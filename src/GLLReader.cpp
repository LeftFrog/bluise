#include <iostream>
#include "Game.h"
#include <vector>
#include "gll_syntax_error.h"

namespace {
    istream& operator>>(istream& is, vector<Game>& games) {
        while(!is.eof()) {
            string line;
            string name;
            string working_directory;
            string executable;
            string save_path;
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
            string var;
            is >> var;
            if(var!="working_directory") {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"working_directory\"!");
            }
            is >> var;
            if(var!="=") {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"=\"!");
            }
            std::getline(is, working_directory);
            working_directory = working_directory.substr(1, working_directory.length());
            is >> var;
            if(var!="executable") {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"executable\"!");
            }
            is >> var;
            if(var!="=") {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"=\"!");
            }
            std::getline(is, executable);
            executable = executable.substr(1, executable.length());
            is >> var;
            if(var!="save_path") {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"save_path\"!");
            }
            is >> var;
            if(var!="=") {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"=\"!");
            }
            std::getline(is, save_path);
            save_path = save_path.substr(1, save_path.length());
            is >> var;
            if(var!="}") {
                throw gll_syntax_error("Syntax Error!\nThere isnt \"}\"!");
            }
            games.push_back(Game(name, working_directory, executable, save_path));
        }
        return is;
    }
}