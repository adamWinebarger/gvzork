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
    float inventoryWeight = 0.0;
    std::vector<Location> locationsThatExistInTheWorld = {};
    Location currentLocation;
    int caloriesFedToTheElf = 0;
    bool gameStillInProgress = true, ateTheMRE = false, drankCoffee = false;
    std::string DirectionNames[11] = { "North", "Northeast", "East", "Southeast", "South",
         "Southwest", "West", "Northwest", "Secret", "Portal", "Portal"};

    string vector2String(vector<string> target);

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

    //Bonus methods
    void teleport(vector<string> target);
    //void inspect(vector<string> target);
    void inventory(vector<string> target);
    void make(vector<string> target);

};

//May as well just do setup here
Game::Game()
{
    srand(time(0)); //For our RNG's
    doSetup();

}

void Game::doSetup() {
    //woodring = NPC("Prof. Woodring", "The Computer Science Professor");
    //Items
    map<string, Item> inGameItems = itemSetup();

    //NPC
    map<string, NPC> npcs = NPCSetup();


    locationSetup(npcs, inGameItems);
    //cout << currentLocation << endl;
    //meet({"Magical Elf"});
    //take({"Master Sword"});
    //inventory({});
    cout << currentLocation << endl;;
    cout << currentLocation.getVisit() << endl;
    currentLocation.setVisit();
    go({"North"});
    go({"South"});
    go({"North"});
    go({"South"});
}

map<string, Item> Game::itemSetup() {
    map<string, Item> inGameItems = {};

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
        inGameItems.insert({"Water", Item("Water", "Needed for life", 0.5)});
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
void Game::locationSetup(map<string, NPC> npcList, map<string, Item> itemList) {
    //First we should probably set up our locations one at a time
    Location theWoods("The Woods", "It's the woods behind Grand Valley's campus. Apparently there's a magical elf that live here. So that's pretty neat",
        {npcList.at("MagicalElf"), npcList.at("Guy")}, {itemList.at("Sword"),
            itemList.at("CoffeeMug2"), itemList.at("Rock")
        });

    Location mackHall("Mack hall", "The computer science building. Just don't think about stealing any computers for the lab",
        {npcList.at("Woodring"), npcList.at("NPC2"), npcList.at("NPC5")}, {itemList.at("GranolaBar"), itemList.at("WaterBottle"), itemList.at("Banana"), itemList.at("laptop")}
    );

    Location padnos("Padnos Hall", "Whole lotta science going on here. This would be a great starter location... IF WE HAD ONE!",
        {npcList.at("padnosProf"), npcList.at("NPC5")}, {itemList.at("Mushroom"), itemList.at("MRE"), itemList.at("laptop")}
    );

    Location clockTower("The Clock Tower", "Anyone can rent this place out, apparently... Looks like today it's the abortion crazies again.",
        {npcList.at("abc1"), npcList.at("abc2"), npcList.at("abc3")}, {itemList.at("WeirdSauce")}
    );

    Location kirkhoff("Kirkhoff hall", "Home of the vet's center and Panda express. Also, there's a pretty good coffee maker here",
    {}, {itemList.at("CoffeeGrounds"), itemList.at("MRE"), itemList.at("Rock")}
    );

    Location library("The Library", "Probably the weirdest library you'll ever see in your life", {}, {itemList.at("WaterBottle"), itemList.at("Banana"), itemList.at("GranolaBar")});

    Location superior("Superior hall", "A lot of art stuff happens here. Pretty sure one of the devs has a photography class in here",
    {npcList.at("artProf"), npcList.at("NPC5")}, {itemList.at("Banana"), itemList.at("laptop"), itemList.at("GranolaBar")}
    );

    Location footBridge("Footbridge", "The pedestrian bridge over the creek",
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

    kirkhoff.addLocation(West, library);
    kirkhoff.addLocation(North, clockTower);
    kirkhoff.addLocation(Northeast, footBridge);
    kirkhoff.addLocation(Southeast, superior);

    theWoods.addLocation(Northwest, mackHall);
    theWoods.addLocation(West,padnos);
    theWoods.addLocation(Southwest, superior);

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
    currentLocation = clockTower;
    currentLocation.setVisit();
}

//Command methods

void Game::show_help() {

}

//Checks if the NPC is in the location, then runs through their dialogue if they're
//in the same location as the character
void Game::talk(string target) {
    string npc = target;

    for (int i = 0; i < currentLocation.getNPCs().size(); i++) {
        if (currentLocation.getNPCs()[i] == npc) {
            NPC currentNPC = currentLocation.getNPCs()[i];

            do {
                currentNPC.getCurrentNPCMessage();
            } while (currentNPC.getMessageNumber() != 0);
            return;
        }
    }

    cout << target << " is not here right now... " << endl;
}

//Shows NPC descriptions
void Game::meet(vector<string> target) {
    ///This will just take what's left of our vector, turn it *back* into a single string, and then compare this string against the names of the NPC's in the NPC vector
    //for the current location
    string npc = vector2String(target);

    for (int i = 0; i < currentLocation.getNPCs().size(); i++) {
        if (currentLocation.getNPCs()[i].getName() == npc) {
            cout << currentLocation.getNPCs()[i].getName() << " - " << currentLocation.getNPCs()[i].getDescription() << endl; //Success. Gives us the description
            currentLocation.setVisit();
            return; //No point in keepingg the loop going
        }
    }
    //Failure message.
    cout << "It would seem that " << npc << " isn't here right now" << endl;
}

//For putting items into your inventory
void Game::take(vector<string> target) {
    string item = vector2String(target);

    //So first we need to check and see if the actual item exists in the location
    for (int i = 0; i < currentLocation.getItems().size(); i++) {

        if (currentLocation.getItems()[i].getName() == item) {
            cout << "Attempting to pick up " << item << "..." << endl; //let them know that the game found it and what's going on

            //Catchment for if this puts us over our weight-limit
            if (currentLocation.getItems()[i].getWeight() + this->inventoryWeight > 30.0) {
                cout << "Cannot pick up " << item << " as you will be overencumbered. Try dropping something first" << endl;
            } else {
                cout << "Item " << item << " added to inventory." << endl;
                this->inventoryWeight += currentLocation.getItems()[i].getWeight();
                playerItems.push_back(currentLocation.getItems()[i]); //gotta actually add the item to the inventory
                currentLocation.takeItem(currentLocation.getItems()[i]); //and then we gotta remember to get rid of it from the world
            }
            return;
        }
    }
}

//This is a bit of a weird one. Basically, it's going to drop the item into the
//world inventory  under normal circumstances. But if give is triggered in the woods
//then it needs to check if the item is edible; and if it is then we need to destroy
// the item and add it to the caloric consumption total for the elf, since hitting
// a ceratin amount there is what triggers the win condition
void Game::give(vector<string> target) {
    string item = vector2String(target);

    //First we need to check that the item is in our inventory
    for (int i = 0; i < playerItems.size(); i++) {
        if (playerItems[i].getName() == item) {
            Item item2Give = playerItems[i];

            //So here we've found the item. Now we need to check
            if (currentLocation.getName() != "The Woods") {
                //So here, we're baically doing take but in reverse: adding item to the world, then clearing it from our inventory.
                this->inventoryWeight -= item2Give.getWeight();
                currentLocation.addItem(item2Give);
                this->playerItems.erase(playerItems.begin() + i);
                cout << item2Give.getName() << "dropped in" << currentLocation.getName() << "." << endl;
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
                NPC elf = currentLocation.getNPCs()[0];

                if (item2Give.getCalories() == 0.0) {
                    cout << elf << endl << "You dick. You need to give me FOOD if you want me to save your school." << endl
                        << "This " << item << " isn't food. Just for this, I'm going to punish you for your insolence and teleport you somewhere random."
                        << endl << "Enjoy." << endl << endl << "You have been teleported" << endl;

                    currentLocation = locationsThatExistInTheWorld[rand() % locationsThatExistInTheWorld.size()];
                }
            }
        }
    }
}

void Game::go(vector<string> target) {
    string destination = vector2String(target);
    Direction d;

    //Catchment for if they say a direction
    for (int i = 0; i < 11; i++) {
        if (DirectionNames[i] == destination) {
            d = (Direction) i;  //since we used enums for direction, we can cast an inte as enum and travel that way
            //cout << d << endl;
            if (d >= 8) {
                //catchment for if someone tries to travel through the portal or secret location through conventional menas
                cout << "You can't travel to that location by conventional means... sorry pal" << endl;
                return;
            }
            //Catchment for if there's nothing in a given direction
            if (currentLocation.getNeighbors().find(d) == currentLocation.getNeighbors().end()) {
                cout << "There's nothing for you in that direction. Nothing you'd want to see anyways." << endl;
                return;
            } else {
                //Success
                string newLoc = currentLocation.getNeighbors().at(d).getName();
                for (int j = 0; j < locationsThatExistInTheWorld.size(); j++)
                    currentLocation = (locationsThatExistInTheWorld[j].getName() == newLoc) ? locationsThatExistInTheWorld[j] : currentLocation;
                currentLocation.setVisit(); //Makes it so the place has been visited
                look({}); //Shows us what's at the new location
                return;
            }
        }
    }
    cout << "Invalid direction detected. You can't go to " << destination << "." << endl;

}

void Game::show_items(vector<string> target) {
    //Somehow forgot this was a method. And im lazy. So I'm just going to call the other inventory method
    inventory({});
}

void Game::look(vector<string> target) {
    //Apparently I made the same mistake with look.
    cout << currentLocation;
}

void Game::quit(vector<string> target) {
    cout << "You failed to save the school." << endl << "Bettter luck next time, nerd" << endl;
    exit(0);
}

//Our optional methods. These will be pretty good

//This one will check for a portal between the current location and the target one
//and that will let the player teleport if... if it's there
void Game::teleport(vector<string> target) {

}

// void Game::inspect(vector<string> target) {
//
// }

void Game::inventory(vector<string> target) {
    for (Item item : playerItems)
        cout << item;
    cout << "Total weight: " << inventoryWeight << endl;
}

void Game::make(vector<string> target) {
    //this could theoretically be build out a little more if we wanted to. But I'm going to use it to make coffee
    string command = vector2String(target);

    if (command == "coffee") {
        bool hasWatter = false, hasGrounds = false, hasCup = false;
        if (currentLocation.getName() != "Kirkhoff hall") {
            cout << "Not in Kirkhoff. Can't make coffee." << endl;
            return;
        }
        for (int i = 0; i < playerItems.size(); i++) {
            hasWatter = (playerItems[i].getName() == "Water bottle" || playerItems[i].getName() =="Water") ? true : hasWatter;
            hasGrounds = (playerItems[i].getName() == "Coffee grounds") ? true : hasGrounds;
            hasCup = (playerItems[i].getName() == "Coffee Mug") ? true : hasCup;
        }

        if (hasWatter && hasGrounds && hasCup)
            playerItems.push_back(Item("Coffee", "Refreshing, and it wakes you up. Guarunteed to make you poop in 20 minutes or less", 0.6, 250));
        return;
    }

    cout << "Unrecognized target for making " << command << ". Please try something else." << endl;
}

//This is just a helper function because I didn't feel like rewriting this same bit of code 8 times.
string Game::vector2String(vector<string> target) {
    string str = accumulate(target.begin(), target.end(), string(),
        [](const string& a, const string& b) -> string {
            return a + (a.length() > 0 ?  " " : "") + b;
    });
    return str;
}
