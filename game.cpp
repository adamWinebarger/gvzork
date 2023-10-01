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
    //Items
    map<string, Item> inGameItems = itemSetup();
    cout << inGameItems.at("Granolabar") << endl;
    cout << inGameItems.at("Banana") << endl;
    cout << inGameItems.at("Cake") << endl;
    cout << inGameItems.at("Green Herb") << endl;
    cout << inGameItems.at("Mushroom") << endl;
    cout << inGameItems.at("Sword") << endl;
    cout << inGameItems.at("Rock") << endl;
    cout << inGameItems.at("Ambrosia") << endl; //8
    cout << inGameItems.at("Relic") << endl;
    cout << inGameItems.at("Water") << endl; //10
    //NPC
    map<string, NPC> npcs = NPCSetup();
    cout << npcs.at("Guy") << endl;
    cout << npcs.at("NPC2") << endl;
    cout << npcs.at("NPC3") << endl;
    cout << npcs.at("NPC4") << endl;
    cout << npcs.at("NPC5") << endl;

    locationSetup();

}

map<string, Item> Game::itemSetup() {
    map<string, Item> inGameItems = {};

        inGameItems.insert({"Banana", Item("Banana", "The fruit that's slightly shaped like a gun. Dispose of peels responsibly", 3, 0.9)});
        //cout << inGameItems.at("Banana") << endl;;
        inGameItems.insert({"Granolabar", Item("Granola bar", "Dry AF, nutritionally questionable, a good snack to give to someone else", 5, 0.1)});
        inGameItems.insert({"Cake", Item("Cake", "The cake is a lie", 300, 5)});
        inGameItems.insert({"Green Herb", Item("Green Herb", "Grown locally in Raccoon City", 10, 0.3)});
        inGameItems.insert({"Mushroom", Item("Mushroom", "May make you Super", 100, 1)});
        inGameItems.insert({"Sword", Item("Master Sword", "Super sharp", 0, 15)});
        inGameItems.insert({"Rock", Item("Rock", "Its not just a boulder Its a rock", 0, 10)});
        inGameItems.insert({"Ambrosia", Item("Ambrosia", "Consumed by the Gods", 400, 1)});
        inGameItems.insert({"Relic", Item("Holy Relic", "It belongs in a museum", 0, 25)});
        inGameItems.insert({"Water", Item("Water", "Needed for life", 0, 0.5)});
    return inGameItems;
}

map<string, NPC> Game::NPCSetup() {
    map<string, NPC> npcList = {};
    //add 5
    npcList.insert({"Guy", NPC("Some Guy","Just a guy",{"How do you do?", "Something something something"})});
    npcList.insert({"NPC2", NPC("NPC2","yep",{"hi", "See ya"})});
    npcList.insert({"NPC3", NPC("NPC3","something",{"Hello", "Goodbye"})});
    npcList.insert({"NPC4", NPC("NPC4","nope",{"Leave me", "get out of here"})});
    npcList.insert({"NPC5", NPC("NPC5","Tall",{"sup", "How it going"})});
    return npcList;
}

void Game::locationSetup() {

}
