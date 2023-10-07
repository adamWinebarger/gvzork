#include <iostream>
//#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <string>
#include <exception>
#include <bits/stdc++.h>
#include<cstdlib>
#include <functional>
#include <cstring>
#include <ctime>
#include <chrono>

#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>


#include "item.h"
#include "location.hpp"
#include "npc.hpp"
#include "direction.h"

//#define Command std::function<void(std::vector<std::string>)>
//#define Command function<void(*)(std::vector<string>)>
#define Command void(Game::*)(std::vector<std::string>)

//typedef void (&Command)(std::vector<std::string>);

class Game {
private:
    Location emptyLoc;

    std::map<std::string, Command> commands = {};
    std::vector<Item> playerItems = {};
    float inventoryWeight = 0.0;
    std::vector<std::reference_wrapper<Location>> locationsThatExistInTheWorld = {};
    std::reference_wrapper<Location> currentLocation = emptyLoc;
    int caloriesFedToTheElf = 0;
    bool gameStillInProgress = true, ateTheMRE = false, drankCoffee = false; //I don't think we're actually going to use these.
    std::string DirectionNames[11] = { "north", "northeast", "east", "southeast", "south",
         "southwest", "west", "northwest", "secret", "portal", "portal"};

    std::string vector2String(std::vector<std::string> target);

    //Our locations so that way we can keep not in the stack
    Location theWoods, mackHall, padnos, clockTower, kirkhoff, library, superior, footBridge;

public:
    Game();
    void doSetup();
    std::map<std::string, Item> itemSetup();
    std::map<std::string, NPC> NPCSetup();
    void locationSetup(std::map<std::string, NPC> npcList, std::map<std::string, Item> itemList);
    std::map<std::string, void(*)(std::vector<std::string>)> setupCommand();
    void commandSetup();


    Location randomLocation();
    void play();

    //Command methods
    void show_help(std::vector<std::string> target);
    void talk(std::vector<std::string> target);
    void meet(std::vector<std::string> target);
    void take(std::vector<std::string> target);
    void give(std::vector<std::string> target);
    void go(std::vector<std::string> target);
    void show_items(std::vector<std::string> target);
    void look(std::vector<std::string> target);
    void quit(std::vector<std::string> target);
    void eat(std::vector<std::string> target);

    //Bonus methods
    void teleport(std::vector<std::string> target);
    //void inspect(vector<string> target);
    void inventory(std::vector<std::string> target);
    void make(std::vector<std::string> target);
    void dumb(std::vector<std::string> target);

    void playGame();

};

//May as well just do setup here
Game::Game()
{

    srand(time(0)); //For our RNG's
    doSetup();
    commandSetup();

}

void Game::doSetup() {
    //woodring = NPC("Prof. Woodring", "The Computer Science Professor");
    //Items
    std::map<std::string, Item> inGameItems = itemSetup();

    //NPC
    std::map<std::string, NPC> npcs = NPCSetup();


    locationSetup(npcs, inGameItems);
    //cout << currentLocation << endl;
    //meet({"Magical Elf"});
    //take({"Master Sword"});
    //inventory({});
    //cout << currentLocation << endl;;
    //currentLocation.get().setVisit();
    //go({"North"});
    //go({"South"});
    commandSetup();
    playGame();
}

void Game::playGame() {

    std::cout << "\tGVZork" << std::endl;
    look({});
    //cout << endl;
    std::string input = "banana";
    std::vector<std::string> comp;

    do {
        getline(std::cin, input);
        boost::trim_left(input);
        input = (input.length() >= 1) ? input : "dumb";
        std::istringstream ss(input);
        for (std::string str; ss >> str; )
            comp.push_back(str);
        std::string command = comp[0];
        std::cout << "\n";
        //cout << command << endl;
        if (commands.find(command) == commands.end())
            std::cout << "Unrecognized command: '" << command << "'. Please input 'help' or 'show_help' for a list of valid commands." << std::endl;
        else {
            comp.erase(comp.begin());
            //cout << comp[0];
            ((this->*commands[command])(comp));
        }

        comp.clear();

    } while (caloriesFedToTheElf < 1000);

    std::cout << std::endl << std::endl << "\tVictory!!!" << std::endl << "Congratulations. You won the game!" << std::endl
        << "Now you have the opportunity to continue giving the university around $14k a year!" << std::endl
        << "Good job!" << std::endl;

}

std::map<std::string, Item> Game::itemSetup() {
    std::map<std::string, Item> inGameItems = {};

        inGameItems.insert({"Banana", Item("Banana", "The fruit that's slightly shaped like a gun. Dispose of peels responsibly", 0.9, 3)});
        //cout << inGameItems.at("Banana") << endl;;
        inGameItems.insert({"GranolaBar", Item("Granola bar", "Dry AF, nutritionally questionable, a good snack to give to someone else", 0.1, 10)});
        inGameItems.insert({"Cake", Item("Cake", "The cake is a lie", 5.0, 300)});
        inGameItems.insert({"Green Herb", Item("Green Herb", "Grown locally in Raccoon City", 0.3, 10)});
        inGameItems.insert({"Mushroom", Item("Mushroom", "May make you Super", 1.0, 100)});
        inGameItems.insert({"Sword", Item("Master Sword", "Super sharp, not very edible", 15.0)});
        inGameItems.insert({"Rock", Item("Rock", "Its not just a boulder Its a rock", 10.0)});
        inGameItems.insert({"Ambrosia", Item("Ambrosia", "Consumed by the Gods", 1.0, 400)});
        inGameItems.insert({"Relic", Item("Holy Relic", "It belongs in a museum", 25.0)});
        inGameItems.insert({"MRE", Item("MRE", "Very filling. But it'll be a while before you poop again", 2.0, 1500)});
        inGameItems.insert({"CoffeeGrounds", Item("Coffee grounds", "Used for coffee. Can be eaten raw if you really need a pick-me-up", 0.1, 15)});
        inGameItems.insert({"WaterBottle", Item("Water bottle", "Sweet, delicious agua", 0.5)});
        inGameItems.insert({"CoffeeMug", Item("Coffee Mug", "It's a mug. For coffee. Could probably used for other things too", 0.1)});
        inGameItems.insert({"CoffeeMug2", Item("Coffee Mug", "It's a mug. For coffee. Could probably used for other things too... what's it doing out here?", 0.1)});
        inGameItems.insert({"Coffee", Item("Coffee", "Refreshing, and it wakes you up. Guarunteed to make you poop in 20 minutes or less", 0.6, 250)});
        inGameItems.insert({"WeirdSauce", Item("Weird Sauce", "A strange sauce given to you by the abortion crazies. Kinda looks like pizza sauce. Not sure I'd eat it", 0.4, 150)});
        inGameItems.insert({"laptop", Item("Laptop", "It's an unsecured laptop. I'm sure no-one will miss it if you pocket it", 5.0)});

        return inGameItems;
}

//Our helper method for setting up the NPC's
std::map<std::string, NPC> Game::NPCSetup() {
    std::map<std::string, NPC> npcList = {};
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

    npcList.insert({"abc1", NPC("Abortion Crazy #1", "One of the abortion crazies. Looks like this one might be the leader. He keeps going on about \"Special suace\"... weird",
        {"You sir, look like a fine upstanding person!", "Did you that by the time a fetus is 6 weeks old, that it could practically fill out the jars we have on that table?",
            "<gestures to table>", "In fact, planned parenthood feels that is the ideal time to kill the unborn and then sell them to dominoes!",
            "Be sure to take one of these jars and really... think about whether you want them to be able to do that", "Now BEGONE YE!"
        }
    )});

    npcList.insert({"abc2", NPC("Abortion crazy #2", "Another one of the abortion crazies. This dude kind of looks like he feels out of place at the clock tower", {
        "Hey how's it going?", "I built that cross that we set up at our stand.", "Yeah, I know it's not the greatest... it's basically just some 2x4's and some bungie cords",
        "But still, Jesus was a carpenter and I want to live up to his expectations!", "Tbh, I don't really want to be here. But the guy in charge said I could build the cross if I came today",
        "I'm starting to think that might've been a mistake"
    })});

    npcList.insert({"abc3", NPC("Abortion crazy #3", "Another one of the abortion crazies. This one really looks like he regrets coming here.", {
        "Hey how's it going?", "Yeah I just came here in the hopes of picking up some hot conservative chicks.", "Yes... just like that episode of 'It's always Sunny'",
        "TBH, I kinda regret my decision.", "Anywho, you should probably talk to one of the other guys if you're actually interested in this stuff"
    })});

    npcList.insert({"padnosProf", NPC("A professor", "Just a science professor.", {
        "Hey how's it going?", "I'm a science professor and you're in Padnos.", "I'm not super relevant to the story, so don't expect a whole lot of detail about my life",
        "Fun fact: My wife was killed by a drug cartel.", "Anyways, I've got more science to go and do.", "I'll see you later"
    })});

    npcList.insert({"artProf", NPC("Art professor", "Not much is known about the art professors. But they probably like art", {
        "Hello!", "I am an art professor.", "I can teach you about art.", "But I imagine you're here for other reasons.", "Please don't steal anything."
    })});

    //add 5
    npcList.insert({"Guy", NPC("Some Guy","Just a guy",
        {"How do you do?", "Something something something", "I'm just a guy. No real distinguishing features.", "Yup, I'm just here, doing my thing. You know how it goes",
            "Hey do you think I could get away with skipping prof. Woodring's class today?", "I think I'm going to risk it.", "Ok. See ya."
        }
    )});
    npcList.insert({"NPC2", NPC("NPC2","yep",{"hi", "See ya"})});
    npcList.insert({"NPC3", NPC("NPC3","something",{"Hello", "Goodbye"})});
    npcList.insert({"NPC4", NPC("NPC4","nope",{"Leave me", "get out of here"})});
    npcList.insert({"NPC5", NPC("NPC5","Tall",{"sup", "How it going"})});


    return npcList;
}

//This is how we'll be getting the locations into the world, as well as how we'll determine the currentLocation of the character
void Game::locationSetup(std::map<std::string, NPC> npcList, std::map<std::string, Item> itemList) {
    //First we should probably set up our locations one at a time
    theWoods = Location("The Woods", "It's the woods behind Grand Valley's campus. Apparently there's a magical elf that live here. So that's pretty neat",
        {npcList.at("MagicalElf"), npcList.at("Guy")}, {itemList.at("Sword"),
            itemList.at("CoffeeMug2"), itemList.at("Rock")
        });

    mackHall = Location("Mack hall", "The computer science building. Just don't think about stealing any computers for the lab",
        {npcList.at("Woodring"), npcList.at("NPC2"), npcList.at("NPC5")}, {itemList.at("GranolaBar"), itemList.at("WaterBottle"), itemList.at("Banana"), itemList.at("laptop")}
    );

    padnos = Location("Padnos Hall", "Whole lotta science going on here. This would be a great starter location... IF WE HAD ONE!",
        {npcList.at("padnosProf"), npcList.at("NPC5")}, {itemList.at("Mushroom"), itemList.at("MRE"), itemList.at("laptop")}
    );

    clockTower = Location("The Clock Tower", "Anyone can rent this place out, apparently... Looks like today it's the abortion crazies again.",
        {npcList.at("abc1"), npcList.at("abc2"), npcList.at("abc3")}, {itemList.at("WeirdSauce")}
    );

    kirkhoff = Location("Kirkhoff hall", "Home of the vet's center and Panda express. Also, there's a pretty good coffee maker here",
    {}, {itemList.at("CoffeeGrounds"), itemList.at("MRE"), itemList.at("Rock")}
    );

    library = Location("The Library", "Probably the weirdest library you'll ever see in your life", {}, {itemList.at("WaterBottle"), itemList.at("Banana"), itemList.at("GranolaBar")});

    superior = Location("Superior hall", "A lot of art stuff happens here. Pretty sure one of the devs has a photography class in here",
    {npcList.at("artProf"), npcList.at("NPC5")}, {itemList.at("Banana"), itemList.at("laptop"), itemList.at("GranolaBar")}
    );

    footBridge = Location("Footbridge", "The pedestrian bridge over the creek",
        {npcList.at("NPC5"), npcList.at("NPC4"), npcList.at("NPC3"), npcList.at("NPC2"), npcList.at("Guy")}, {}
    );

    //The next step will be adding each location to its respective neighbor map in each other location
    //to make a sort of cohesive world
    mackHall.addLocation(South, padnos);
    mackHall.addLocation(Southeast, theWoods);
    mackHall.addLocation(OneWayPortal, superior);
    mackHall.addLocation(TwoWayPortal, kirkhoff);

    padnos.addLocation(East, theWoods);
    padnos.addLocation(North, mackHall);
    padnos.addLocation(Southeast, footBridge);
    padnos.addLocation(South, clockTower);

    clockTower.addLocation(North, padnos);
    clockTower.addLocation(East, footBridge);
    clockTower.addLocation(Southwest, library);
    clockTower.addLocation(South, kirkhoff);
    clockTower.addLocation(Southeast, superior);
    clockTower.addLocation(OneWayPortal, mackHall);

    kirkhoff.addLocation(West, library);
    kirkhoff.addLocation(North, clockTower);
    kirkhoff.addLocation(Northeast, footBridge);
    kirkhoff.addLocation(Southeast, superior);
    kirkhoff.addLocation(TwoWayPortal, mackHall);

    theWoods.addLocation(Northwest, mackHall);
    theWoods.addLocation(West,padnos);
    theWoods.addLocation(Southwest, superior);
    theWoods.addLocation(OneWayPortal, footBridge);

    footBridge.addLocation(North, mackHall);
    footBridge.addLocation(Northwest, padnos);
    footBridge.addLocation(West, clockTower);
    footBridge.addLocation(Southwest, kirkhoff);
    footBridge.addLocation(South, superior);

    library.addLocation(East, kirkhoff);
    library.addLocation(Northeast, clockTower);

    superior.addLocation(Northeast, theWoods);
    superior.addLocation(Northwest, kirkhoff);
    superior.addLocation(North, footBridge);


    //then we'll add each of those fully built locations to our locationsThatExistVector,I guess
    locationsThatExistInTheWorld.push_back(mackHall);
    locationsThatExistInTheWorld.push_back(padnos);
    locationsThatExistInTheWorld.push_back(clockTower);
    locationsThatExistInTheWorld.push_back(kirkhoff);
    locationsThatExistInTheWorld.push_back(theWoods);
    locationsThatExistInTheWorld.push_back(footBridge);
    locationsThatExistInTheWorld.push_back(library);
    locationsThatExistInTheWorld.push_back(superior);

    //I was going to make a standalone function that decided the random location that the play will
    //start in. But now I'm kind of thinking that we should just do it in here.
    //currentLocation = locationsThatExistInTheWorld[rand() % locationsThatExistInTheWorld.size()];
    int locationInteger = rand() % locationsThatExistInTheWorld.size();
    locationsThatExistInTheWorld[locationInteger].get().setVisit();
    currentLocation.get() = locationsThatExistInTheWorld[locationInteger];
    //clockTower.setVisit();
    //currentLocation.get() = clockTower;

    //currentLocation.setVisit();
}

void Game::commandSetup() {
    //commands.insert(make_pair("go", &Game::go));

    //Help
    commands["help"] = &Game::show_help;
    commands["show_help"] = &Game::show_help;

    commands["talk"] = &Game::talk;

    commands["grab"] = &Game::take;
    commands["take"] = &Game::take;

    commands["give"] = &Game::give;
    commands["drop"] = &Game::give;

    commands["go"] = &Game::go;
    commands["move"] = &Game::go;

    commands["inventory"] = &Game::inventory;
    commands["show_items"] = &Game::inventory; //these do exactly the same thing... lol
    commands["items"] = &Game::inventory;

    commands["look"] = &Game::look;
    commands["current_location"] = &Game::look;
    commands["look_around"] = &Game::look;
    commands["ls"] = &Game::look;

    commands["teleport"] = &Game::teleport;
    commands["portal"] = &Game::teleport;

    commands["make"] = &Game::make;

    commands["meet"] = &Game::meet;

    commands["eat"] = &Game::eat;

    commands["dumb"] = &Game::dumb;

    commands["quit"] = &Game::quit;
}


//Command methods

void Game::show_help(std::vector<std::string> target) {
    std::cout << "\tgvzork Help Menu: " << std::endl << "\nActions - Commands" << std::endl;
    std::cout << "Help - help, show_help" << std::endl << "Talk to NPCs - talk" << std::endl
        << "Pick up items - grab, take" << std::endl << "Eat food - eat" << std::endl
        << "Travel to other locaiton - go, move" << std::endl << "Get rid of item/feed the elf - give, drop"
        << std::endl << "Show inventory - inventory, show_items, items" << std::endl
        << "Look around (show location prompt) - look, current_location, look_around, ls"
        << std::endl << "Use a portal/secret travel option - teleport, portal" << "craft iems (coffee) - make" << std::endl;

    //Still need to put the timestamp in here.
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm* timeinfo = localtime(&timenow); //fuck it. We're using a pointer here because this seems like the easiest way to print time the way I want to do that
    //It's technically on the stack so it doesn't count, right?
    char timestr[80];
    strftime(timestr, 80, "Time: %T", timeinfo);

    std::cout << "Current time " << timestr << "." << std::endl;
}

void Game::dumb(std::vector<std::string> target) {
    std::cout << "\nInput something in the prompt, dumbass." << std::endl;
}

//Checks if the NPC is in the location, then runs through their dialogue if they're
//in the same location as the character
void Game::talk(std::vector<std::string> target) {
    std::string npc = vector2String(target);

    for (int i = 0; i < currentLocation.get().getNPCs().size(); i++) {
        if (boost::iequals(currentLocation.get().getNPCs()[i].getName(), npc)) {
            NPC currentNPC = currentLocation.get().getNPCs()[i];

            std::cout << std::endl << currentNPC;

            do {
                std::cout << currentNPC.getCurrentNPCMessage() << std::endl;
            } while (currentNPC.getMessageNumber() != 0);
            return;
        }
    }

    std::cout << npc << " is not here right now... " << std::endl;
}

//Shows NPC descriptions
void Game::meet(std::vector<std::string> target) {
    ///This will just take what's left of our vector, turn it *back* into a single string, and then compare this string against the names of the NPC's in the NPC vector
    //for the current location
    std::string npc = vector2String(target);

    for (int i = 0; i < currentLocation.get().getNPCs().size(); i++) {
        if (boost::iequals(currentLocation.get().getNPCs()[i].getName(), npc)) {
            std::cout << currentLocation.get().getNPCs()[i].getName() << " - " << currentLocation.get().getNPCs()[i].getDescription() << std::endl; //Success. Gives us the description
            currentLocation.get().setVisit();
            return; //No point in keepingg the loop going
        }
    }
    //Failure message.
    std::cout << "It would seem that " << npc << " isn't here right now" << std::endl;
}

//For putting items into your inventory
void Game::take(std::vector<std::string> target) {
    std::string item = vector2String(target);

    //So first we need to check and see if the actual item exists in the location
    for (int i = 0; i < currentLocation.get().getItems().size(); i++) {

        if (boost::iequals(currentLocation.get().getItems()[i].getName(), item)) {
            std::cout << "Attempting to pick up " << item << "..." << std::endl; //let them know that the game found it and what's going on

            //Catchment for if this puts us over our weight-limit
            if (currentLocation.get().getItems()[i].getWeight() + this->inventoryWeight > 30.0) {
                std::cout << "Cannot pick up " << item << " as you will be overencumbered. Try dropping something first" << std::endl;
            } else {
                std::cout << "Item " << item << " added to inventory." << std::endl;
                this->inventoryWeight += currentLocation.get().getItems()[i].getWeight();
                playerItems.push_back(currentLocation.get().getItems()[i]); //gotta actually add the item to the inventory
                currentLocation.get().takeItem(currentLocation.get().getItems()[i]); //and then we gotta remember to get rid of it from the world
            }
            return;
        }
    }

    std::cout << "Unable to pick up " << item << " as it is not here." << std::endl;
}

//This is a bit of a weird one. Basically, it's going to drop the item into the
//world inventory  under normal circumstances. But if give is triggered in the woods
//then it needs to check if the item is edible; and if it is then we need to destroy
// the item and add it to the caloric consumption total for the elf, since hitting
// a ceratin amount there is what triggers the win condition
void Game::give(std::vector<std::string> target) {
    std::string item = vector2String(target);

    //First we need to check that the item is in our inventory
    for (int i = 0; i < playerItems.size(); i++) {
        if (boost::iequals(playerItems[i].getName(), item)) {
            Item item2Give = playerItems[i];

            //So here we've found the item. Now we need to check
            if (currentLocation.get().getName() != "The Woods") {
                //So here, we're baically doing take but in reverse: adding item to the world, then clearing it from our inventory.
                this->inventoryWeight -= item2Give.getWeight();
                currentLocation.get().addItem(item2Give);
                this->playerItems.erase(playerItems.begin() + i);
                std::cout << item2Give.getName() << "dropped in " << currentLocation.get().getName() << "." << std::endl;
                return; //and now there's nothing left to do so we're going to exit this method
            } else {
                //So this is what's going to happen if we're in the woods. Basically we need a condition that's kind of like the other one.
                //But it's going to first check that the calorie value is not set to 0. If it is, then the only thing that needs to happen is player
                //get's teleported to some random place (currentLocation's value changes to a random value in our Location vector).
                //
                //Then if the calorie count is anything other than 0, we need to increment the elf's calorie shit by that value, then remove the item from player inventory
                //and not drop it in the world because that item has been "eaten". I think that's all we need to do here

                //You know what? We're just going to have one character or maybe 2 out in the woods and we're just going to have it so that elf is first in the NPC vector in order to make this
                //Easier on ourselves
                NPC elf = currentLocation.get().getNPCs()[0];

                if (item2Give.getCalories() == 0.0) {
                    std::cout << elf << std::endl << "You dick. You need to give me FOOD if you want me to save your school." << std::endl
                        << "This " << item << " isn't food. Just for this, I'm going to punish you for your insolence and teleport you somewhere random."
                        << std::endl << "Enjoy." << std::endl << std::endl << "You have been teleported" << std::endl;

                    currentLocation = locationsThatExistInTheWorld[rand() % locationsThatExistInTheWorld.size()];
                    return;

                } else {
                    this->inventoryWeight -= item2Give.getWeight();
                    caloriesFedToTheElf += item2Give.getCalories();
                    this->playerItems.erase(playerItems.begin() + i);
                    std::cout << "You gave " << item2Give.getName() << " to the elf." << std::endl
                        << "The elf is now " << item2Give.getCalories() << " fuller.\nGood job" << std::endl
                        << "You have now fed the elf " << caloriesFedToTheElf << " calories.\n" << std::endl;
                    return;
                }
            }
        }
    }

    std::cout << "I'm not sure what you are trying to give the elf. But you don't have that in your inventory.\n Probably better you don't try that again" << std::endl;
}

void Game::eat(std::vector<std::string> target) {
    std::string item = vector2String(target);

    //So we're going to go something similar to what we did with giving the elf food. But make is so that we can eat
    // food items as well. We won't get anything from it. But it will be funny.
    for (int i = 0; i < playerItems.size(); i++) {

        //first catch: we find that the item exists in our inventory
        if (boost::iequals(item, playerItems[i].getName())) {

            //first catch: we find out that the item isn't edible (calories = 0)
            if (playerItems[i].getCalories() == 0) {
                std::cout << "Yeah... you can't eat that" << std:: endl;
                return;
            }

            //next catch: it's edible
            playerItems.erase(playerItems.begin() + i);
            std::cout << "You have eaten the " << item << "...\nYou don't get anything for eating items in this game. But... you did it.\nSo... good job, I guess"
                << std::endl;
            return;
        }
    }

    std::cout << "You can't eat '" << item << "' as you don't have that in your inventory." << std::endl;
}

//So now we have to rewrite this to handle our reference_wrapper<Location> objects... fun
void Game::go(std::vector<std::string> target) {
    std::string destination = vector2String(target);
    Direction d;

    //Catchment for if they say a direction
    // for (int i = 0; i < 11; i++) {
    //     if (DirectionNames[i] == destination) {
    //         d = (Direction) i;  //since we used enums for direction, we can cast an inte as enum and travel that way
    //         //cout << d << endl;
    //         if (d >= 8) {
    //             //catchment for if someone tries to travel through the portal or secret location through conventional menas
    //             cout << "You can't travel to that location by conventional means... sorry pal" << endl;
    //             return;
    //         }
    //         //Catchment for if there's nothing in a given direction
    //         if (currentLocation.getNeighbors().find(d) == currentLocation.getNeighbors().end()) {
    //             cout << "There's nothing for you in that direction. Nothing you'd want to see anyways." << endl;
    //             return;
    //         } else {
    //             //Success
    //             string newLoc = currentLocation.getNeighbors().at(d).getName();
    //             for (int j = 0; j < locationsThatExistInTheWorld.size(); j++)
    //                 currentLocation = (locationsThatExistInTheWorld[j]. == newLoc) ? locationsThatExistInTheWorld[j] : currentLocation;
    //             currentLocation.setVisit(); //Makes it so the place has been visited
    //             look({}); //Shows us what's at the new location
    //             return;
    //         }
    //     }
    // }
    // cout << "Invalid direction detected. You can't go to " << destination << "." << endl;

    for (int i = 0; i < 11; i++) {
        //Catchment for when we find a direction match
        if (boost::iequals(destination, DirectionNames[i])) {

            //Catchment for the fact that we want to not be able to use portals and shit via go, despite the fact that they're
            //in the direction map
            if (i >= 8) {
                std::cout << "You cannot travel via " << DirectionNames[i] << " by convetional means. Sorry." << std::endl;
                return;
            }

            d = (Direction) i;

            //Catchment for if nothing exists in that direction
            if (currentLocation.get().getNeighbors().count(d) < 1) {
                std::cout << "Nothing exists " << DirectionNames[d] << " of here. Nothing you would want to see anyways" << std::endl;
                return;
            }
            std::cout << "Passed bad direction catchment" << std::endl;
            //cout << currentLocation.get().getNeighbors().at(d).get().getName() << endl;

            //So I guess this is where our success shit would happen
            //cout << currentLocation.getNeighbors().at(d) << endl;
            currentLocation.get().getNeighbors().at(d).get().setVisit();
            currentLocation = currentLocation.get().getNeighbors().at(d); //this should be all we need now that we're doing reference wrappers
            //currentLocation.setVisit();
            look({});
            return;
        }
    }
    std::cout << "Invalid direction detected. You cannot travel " << destination << "." << std::endl;

}

void Game::show_items(std::vector<std::string> target) {
    //Somehow forgot this was a method. And im lazy. So I'm just going to call the other inventory method
    inventory({});
}

void Game::look(std::vector<std::string> target) {
    //Apparently I made the same mistake with look.
    std::cout << currentLocation.get();
}

void Game::quit(std::vector<std::string> target) {
    std::cout << "You failed to save the school." << std::endl << "Bettter luck next time, nerd" << std::endl;
    exit(0);
}

//Our optional methods. These will be pretty good

//This one will check for a portal between the current location and the target one
//and that will let the player teleport if... if it's there
void Game::teleport(std::vector<std::string> target) {
    std::string teleportal= vector2String(target);

    Direction d;

    //Ok, so here, we need to do things a little differently. I think similar to how our display neighbors method works
    // basically, we're going to pass the name of the location on the other side of the "portal", then we need to check that
    // that location exists as a neighbor to the current one AND if it's direction key is greater than or equal to 8... seems easy
    // enough since we wrote it out first.

    for (int i = 8; i < 11; i++) {

        //iterating through conventional means wasn't working here. So we're going to get really dumb with it
        //Checking to see if something exists at a given "secret" location on the map
        if (currentLocation.get().getNeighbors().count((Direction) i) == 1) {

            if (boost::iequals(currentLocation.get().getNeighbors().at((Direction) i).get().getName(), teleportal)) {
                std::cout << "Teleporting to " << teleportal << "..." << std::endl << std::endl;
                currentLocation.get().getNeighbors().at((Direction) i).get().setVisit();
                currentLocation = currentLocation.get().getNeighbors().at((Direction) i);
                look({});
                return;
            }
        }
    }

   //I guess let's do a catchment for if the place exists but you can't teleport to there from here
   for (int j = 0; j < locationsThatExistInTheWorld.size(); j++)
       if (boost::iequals(locationsThatExistInTheWorld[j].get().getName(), teleportal)) {
           std::cout << "You can not teleport to " << teleportal << " from here." << std::endl;
           return;
    }

    //And then a catchment for if the place just straight up doesn't exist
    std::cout << "I am not sure where you are trying to go to. Be sure to type 'teleport' followed by the location name that you are trying to go to." << std::endl;

}

// void Game::inspect(vector<string> target) {
//
// }

void Game::inventory(std::vector<std::string> target) {
    for (Item item : playerItems)
        std::cout << item;
    std::cout << "Total weight: " << inventoryWeight << std::endl;
}

void Game::make(std::vector<std::string> target) {
    //this could theoretically be build out a little more if we wanted to. But I'm going to use it to make coffee
    std::string command = vector2String(target);

    if (boost::iequals(command, "coffee")) {
        bool hasWatter = false, hasGrounds = false, hasCup = false;
        if (currentLocation.get().getName() != "Kirkhoff hall") {
            std::cout << "Not in Kirkhoff. Can't make coffee." << std::endl;
            return;
        }
        for (int i = 0; i < playerItems.size(); i++) {
            hasWatter = (boost::iequals(playerItems[i].getName(), "Water bottle")) ? true : hasWatter;
            hasGrounds = (boost::iequals(playerItems[i].getName(), "Coffee grounds")) ? true : hasGrounds;
            hasCup = (boost::iequals(playerItems[i].getName(), "Coffee Mug")) ? true : hasCup;
        }

        if (hasWatter && hasGrounds && hasCup) {
            playerItems.erase(std::remove(playerItems.begin(), playerItems.end(), "Coffee grounds"));
            playerItems.erase(std::remove(playerItems.begin(), playerItems.end(), "Coffee Mug"));
            playerItems.erase(std::remove(playerItems.begin(), playerItems.end(), "Water Bottle"));
            playerItems.push_back(Item("Coffee", "Refreshing, and it wakes you up. Guarunteed to make you poop in 20 minutes or less", 0.6, 250));
            std::cout << "Coffee has been added to your inventory... I hope it was worth it." << std::endl;
        }
        return;
    }

    std::cout << "Unrecognized target for making " << command << ". Please try something else." << std::endl;
}

//This is just a helper function because I didn't feel like rewriting this same bit of code 8 times.
std::string Game::vector2String(std::vector<std::string> target) {
    std::string str = accumulate(target.begin(), target.end(), std::string(),
        [](const std::string& a, const std::string& b) -> std::string {
            return a + (a.length() > 0 ?  " " : "") + b;
    });
    return str;
}
