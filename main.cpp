#include "Interface.h"
#include <iostream>

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