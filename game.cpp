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


using namespace std;



class Game {
private:
    map<string, Command> commands = {};
    std::vector<Item> playerItems = {};
    int inventoryWeight = 0;
    std::vector<Location> locationsThatExistInTheWorld = {};
    Location currentLocation;
    int caloriesFedToTheElf = 0;
    bool gameStillInProgress = true, ateTheMRE = false, drankCoffee = false;

public:
    Game();
    void doSetup();
    map<string, Item> itemSetup();
    map<string, NPC> NPCSetup();
    void locationSetup();
};

//May as well just do setup here
Game::Game()
{

    //this->woodring = NPC("Prof Woodring", "He's the CS prof from North Carolina");
    // NPC woodring("Prof. Woodring", "He's the CS prof from North Carolina", {"How do you do?", "Something something something"});
    // cout << woodring << endl;
    // Location l("The woods", "it's the woods");
    // //cout << l << endl;
    // Item i("Piece of shit", "it's a dog turd");
    // cout << i << endl;
    // currentLocation = l;
    // cout << currentLocation << endl;

    //locationsThatExistInTheWorld.push_back(l);

    doSetup();

}

void Game::doSetup() {
    //woodring = NPC("Prof. Woodring", "The Computer Science Professor");
    map<string, Item> inGameItems = itemSetup();
    cout << inGameItems.at("Banana") << endl;
    map<string, NPC> npcs = NPCSetup();
    locationSetup();

}

map<string, Item> Game::itemSetup() {
    map<string, Item> inGameItems = {};

        inGameItems.insert({"Banana", Item("Banana", "The fruit that's slightly shaped like a gun. Dispose of peels responsibly", 3, 0.9)});
        //cout << inGameItems.at("Banana") << endl;;
        inGameItems.insert({"Granolabar", Item("Granola bar", "Dry AF, nutritionally questionable, a good snack to give to someone else", 5, 0.1)});

    return inGameItems;
}

map<string, NPC> Game::NPCSetup() {
    map<string, NPC> npcList = {};

    return npcList;
}

void Game::locationSetup() {

}
