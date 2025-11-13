#include "Interface.h"
#include <iostream>

/**
 *I am just practicing and took some ideas from one of the uploaded codes and expanded a little.
 *I tried to separate classes into three and moreover header and source classes separately.
 *I tested exercise 1.4  and worked , I will prepare pdf for this and the rest in the next days
 * NonOptimized Compile with : g++ -std=c++17 -O0 -g -o game_O0 main.cpp WorldClass.cpp Interface.cpp
 * if wanted to run in different env like macOS , use(clang++)
 * clang++ -std=c++17 -O0 -g -o game_O0 main.cpp WorldClass.cpp Interface.cpp
 * it is for normal compiling. to try different
 * compiler optimization level use -O1, -O2 or -O3
 * to change compiling mood from debug to release :
 * clang++ -std=c++17 -O3 -DNDEBUG -o game_release main.cpp WorldClass.cpp Interface.cpp
 * for ex.1.4 and 1.5 use the predefined autorun methods by commented out
 * @return
 */
int main() {

    Interface interface;
    interface.CLI(); //under normal circumstances
    //interface.autoRun("p67_snark_loop.txt", 2000); // run after disabling print and stability

    // std::vector<std::pair<int, int>> sizes= {
    //     {10,10}, {20,20}, {100, 100}, {1000, 1000}, {100000, 100000}
    // };
    // for (auto[h,w] : sizes)
    //     interface.autoRunWithSize("p67_snark_loop.txt", h, w, 100);
}