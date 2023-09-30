#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>

#include "item.h"
#include "location.hpp"
#include "npc.hpp"
#include "direction.h"

typedef void (&Command)(std::vector<std::string>);

class Game {
private:
    //Alright, so the segfaults were being caused by the default values not being equal in the header and the instantiation of the classes themselves.
    //Fucking remember that because we just spent like 2 hours trying to chase down some phantom segfaults
    std::map<std::string, Command> commands = {};
    std::vector<Item> playerInventory ={};
    int inventoryWeight = 0;
    std::vector<Location> locationsThatExistInTheWorld = {};
    Location currentLocation;
    int caloriesFedToTheElf = 0;
    bool gameStillInProgress = true, ateTheMRE = false, drankCoffee = false;


public:
    Game();
    void doSetup();
    std::map<std::string, Item> itemSetup();
    std::map<std::string, NPC> NPCSetup();
    void locationSetup();
};

#endif
