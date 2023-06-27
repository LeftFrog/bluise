#include "bluise.h"
#include "../command_line_ui/ncurses_ui.cpp"
//#include "../command_line/command_processor.cpp"

inline void saveGLL() {
    sort(games.begin(), games.end());
    ofstream oft(HOME+"/Documents/Bluise/Games.gll", std::ofstream::trunc);
    oft << games;
    oft.close();
}

inline void readGLL() {

    ifstream ist(HOME+"/Documents/Bluise/Games.gll");
    try {
        games.clear();
        ist >> games;
    }
    catch (const invalid_path& err) {
        cerr << err.what();
    }
    catch (const gll_syntax_error& err) {
        cerr << err.what();
    }
 
    ist.close();
}

int main(int argc, char** argv) {  

    readGLL();
    if(argc==1) {
        print_ui();
    }
    else {
        process_command_line(argc, argv);
    }

    return 0;
}