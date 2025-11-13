#include "Interface.h"
#include <iostream>

/**
 * NonOptimized Compile with : g++ -std=c++17 -O0 -g -o game_O0 main.cpp WorldClass.cpp Interface.cpp
 * if wanted to run in different env like macOS using(clang++)
 * clang++ -std=c++17 -O0 -g -o game_O0 main.cpp WorldClass.cpp Interface.cpp
 * it is for normal compiling. to try different
 * compiler optimization level use -O1, -O2 or -O3
 * to change compiling mood from debug to release :
 * clang++ -std=c++17 -O3 -DNDEBUG -o game_release main.cpp WorldClass.cpp Interface.cpp
 *
 * @return
 */
int main() {
    //build your own Grid
    Interface interface;
    interface.CLI();
}