#include <iostream>
#include <string>
#include <vector>
#include <csignal>

// #include "item.h" // Include the item header file
// #include "npc.hpp"
// #include "direction.h"
// #include "location.hpp"
#include "game.h"

// as of right now here to test item
 //we're doing this so I don't have to type a bunch of std shit over and over again

void sigHandler(int signal) {
        std::cout << "\nSIGINT can't save you, loser.\nYou still lose" << std::endl;
        exit(0);
}

int main() {

        std::signal(SIGINT, sigHandler);
        Game();


        //cin.get();
        return 0;
}
