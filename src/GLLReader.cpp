#include "GLLReader.h"
#include "gll_syntax_error.h"

namespace bluise_core{
std::ostream& operator<<(std::ostream& os, QList<Game>& games) {
        for(auto game : games) {
            os << (game.get_name() + " {\n");
            os << ("working_directory = " + game.get_working_directory() + '\n');
            os << ("executable = " + game.get_executable() + '\n');
            os << ("save_path = " + game.get_save_path() + '\n');
            os << "}\n";
        }
        return os;
    }

inline string get_var(const string& var_name, std::istream& is) {
        string var;
        is >> var;
        if(var!=var_name) {
            throw gll_syntax_error("Syntax Error!\nThere isnt \""+var_name+"\"!" + var);
        }
        is >> var;
        if(var!="=") {
            throw gll_syntax_error("Syntax Error!\nThere isnt \"=\"!");
        }
        std::getline(is, var);
        return var.substr(1, var.length());
    }

    std::istream& operator>>(std::istream& is, QList<Game>& games) {
        while(!is.eof()) {
            string line;
            string name;
            std::getline(is, line);
            while(line.empty()&&(!is.eof())){
                std::getline(is, line);
            }
            if(is.eof()) {
                return is;
            }
            short pos = line.find('{');
            if(pos==string::npos) {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"{\"!");
            }
            name = line.substr(0, line.length() - 2);
            string wd = get_var("working_directory", is);
            string ex = get_var("executable", is);
            string sp = get_var("save_path", is);
            Game g(name, wd, ex, sp);
            string var;
            is >> var;
            if(var!="}") {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"}\"!");
            }
            games.push_back(g);
        }
        return is;
    }
}
