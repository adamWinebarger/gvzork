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
    float inventoryWeight = 0.0;
    std::vector<Location> locationsThatExistInTheWorld = {};
    Location currentLocation;
    int caloriesFedToTheElf = 0;
    bool gameStillInProgress = true, ateTheMRE = false, drankCoffee = false;
    std::string DirectionNames[11];

    std::string vector2String(std::vector<std::string> target);


public:
    Game();
    void doSetup();
    std::map<std::string, Item> itemSetup();
    std::map<std::string, NPC> NPCSetup();
    void locationSetup(std::map<std::string, NPC> npcList, std::map<std::string, Item> itemList);

    //Command methods
    void show_help();
    void talk(std::string target);
    void meet(std::vector<std::string> target);
    void take(std::vector<std::string> target);
    void give(std::vector<std::string> target);
    void go(std::vector<std::string> target);
    void show_items(std::vector<std::string> target);
    void look(std::vector<std::string> target);
    void quit(std::vector<std::string> target);

    //Apparently we need two additional commands.
    void teleport(std::vector<std::string> target);
    //void inspect(std::vector<std::string> target);
    void inventory(std::vector<std::string> target);
    void make(std::vector<std::string> target);
};

#endif
