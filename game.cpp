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
    void locationSetup(map<string, NPC> npcList, map<string, Item> itemList);
    map<string, void(*)(vector<string>)> setupCommand();
    Location randomLocation();
    void play();

    //Command methods
    void show_help();
    void talk(string target);
    void meet(vector<string> target);
    void take(vector<string> target);
    void give(vector<string> target);
    void go(vector<string> target);
    void show_items(vector<string> target);
    void look(vector<string> target);
    void quit(vector<string> target);
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
    locationSetup(npcs, inGameItems);

}

map<string, Item> Game::itemSetup() {
    map<string, Item> inGameItems = {};

        inGameItems.insert({"Banana", Item("Banana", "The fruit that's slightly shaped like a gun. Dispose of peels responsibly", 0.9, 3)});
        //cout << inGameItems.at("Banana") << endl;;
        inGameItems.insert({"Granolabar", Item("Granola bar", "Dry AF, nutritionally questionable, a good snack to give to someone else", 0.1, 10)});
        inGameItems.insert({"Cake", Item("Cake", "The cake is a lie", 5.0, 300)});
        inGameItems.insert({"Green Herb", Item("Green Herb", "Grown locally in Raccoon City", 0.3, 10)});
        inGameItems.insert({"Mushroom", Item("Mushroom", "May make you Super", 1.0, 100)});
        inGameItems.insert({"Sword", Item("Master Sword", "Super sharp, not very edible", 15.0)});
        inGameItems.insert({"Rock", Item("Rock", "Its not just a boulder Its a rock", 10.0)});
        inGameItems.insert({"Ambrosia", Item("Ambrosia", "Consumed by the Gods", 1.0, 400)});
        inGameItems.insert({"Relic", Item("Holy Relic", "It belongs in a museum", 25.0)});
        inGameItems.insert({"Water", Item("Water", "Needed for life", 0.5)});
        inGameItems.insert({"MRE", Item("MRE", "Very filling. But it'll be a while before you poop again", 2.0, 1500)});
        inGameItems.insert({"CoffeeGrounds", Item("Coffee grounds", "Used for coffee. Can be eaten raw if you really need a pick-me-up", 0.1, 15)});
        inGameItems.insert({"WaterBottle", Item("Water bottle", "Sweet, delicious agua", 0.5)});
        inGameItems.insert({"CoffeeMug", Item("Coffee Mug", "It's a mug. For coffee. Could probably used for other things too", 0.1)});
        inGameItems.insert({"Coffee", Item("Coffee", "Refreshing, and it wakes you up. Guarunteed to make you poop in 20 minutes or less", 0.6, 250)});

    return inGameItems;
}

map<string, NPC> Game::NPCSetup() {
    map<string, NPC> npcList = {};
    npcList.insert({"Woodring", NPC("Prof. Woodring", "The CS prof from North Carolina",
        {"Howdy, I'm professor Woodring", "I'm from somewhere in North Carolina, but the developers didn't know where specifically from in the state",
            "But that doesn't matter because I'm here to give you the rundown about what's going on here right now.",
            "Basically, president Mantella is planning to destroy the university by raising tuition to the point that no-one can afford to attend here.",
            "Then she's going to try get her pension covered by the taxpayer during bankruptcy proceedings, effectively destroying the university in the process.",
            "What's going to happen after that? Who knows? Maybe it'll turn into a bunch of strip malls.",
            "But there's a magical elf that lives in the woods behind campus. And if you feed him enough stuff, then that elf will leave something on prez's desk that should (hopefully) be enough to get her to abandon her plan.",
            "So yeah. Go around campus and find food, give it to the elf, I'm sure you figured this out by now.",
            "Just come talk to me if you need me to explain this whole spiel to you again"
        }
    )});
    npcList.insert({"MagicalElf", NPC("Magical Elf", "It's the magical elf that's going to save the school", {
        "Hello there!", "I'm the magaical elf of the woods behind Grand Valley", "You can call me Tim.", "Or don't. Your choice",
    })});


    npcList.insert({"Guy", NPC("Some Guy","Just a guy",{"How do you do?", "Something something something"})});
    npcList.insert({"NPC2", NPC("NPC2","yep",{"hi", "See ya"})});
    npcList.insert({"NPC3", NPC("NPC3","something",{"Hello", "Goodbye"})});
    npcList.insert({"NPC4", NPC("NPC4","nope",{"Leave me", "get out of here"})});
    npcList.insert({"NPC5", NPC("NPC5","Tall",{"sup", "How it going"})});

    return npcList;
}

void Game::locationSetup(map<string, NPC> npcList, map<string, Item> itemList) {

}
