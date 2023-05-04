#include <iostream>
#include "Game.h"
#include <vector>

namespace {
    istream& operator>>(istream& is, vector<Game>& games) {
        while(!is.eof()) {
            string line;
            string name;
            string working_directory;
            string executable;
            string save_path;
            std::getline(is, line);
            if(line.empty()) {
                std::getline(is, line);
            }
            short pos = line.find('{');
            if(pos==string::npos) {
                std::cout << "Error1";
            }
            name = line.substr(0, line.length() - 2);
            string var;
            is >> var;
            if(var!="working_directory") {
                std::cout << "Error2";
            }
            is >> var;
            if(var!="=") {
                std::cout << "Error3";
            }
            std::getline(is, working_directory);
            working_directory = working_directory.substr(1, working_directory.length());
            is >> var;
            if(var!="executable") {
                std::cout << "Error4";
            }
            is >> var;
            if(var!="=") {
                std::cout << "Error5";
            }
            std::getline(is, executable);
            executable = executable.substr(1, executable.length());
            is >> var;
            if(var!="save_path") {
                std::cout << "Error6";
            }
            is >> var;
            if(var!="=") {
                std::cout << "Error7";
            }
            std::getline(is, save_path);
            save_path = save_path.substr(1, save_path.length());
            is >> var;
            if(var!="}") {
                std::cout << "Error8";
            }
            games.push_back(Game(name, working_directory, executable, save_path));
        }
        return is;
    }
}