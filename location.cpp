#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <algorithm>

#include "direction.h"
#include "npc.hpp"
#include "item.h"

class Location {

public:

    //Constructor
    Location(std::string name, std::string description, std::vector<NPC> peepsThatLiveHere,
             std::vector<Item> itemsThatLiveHere);
    //Location(std::string name, std::string description);
    Location();

    //Getter for the neighbors
    std::map<Direction, Location> getNeighbors();

    void setVisit();
    bool getVisit();

    void addLocation(Direction direction, Location location);
    void addNPC(NPC npc);
    void addItem(Item item);
    void takeItem(Item item);

    std::vector<NPC> getNPCs();
    std::vector<Item> getItems();

    std::string getName();

    friend std::ostream & operator << (std::ostream &out, const Location &location);


private:
    std::string name, description;
    bool hasBeenVisited = false;
    std::map<Direction, Location> neighbors = {};
    std::vector<NPC> peepsThatLiveHere = {};
    std::vector<Item> itemsThatLiveHere = {};
    std::string DirectionNames[11] = { "North", "Northeast", "East", "Southeast", "South",
         "Southwest", "West", "Northwest", "Secret", "Portal", "Portal"};
};

Location::Location(std::string name, std::string description, std::vector<NPC> peepsThatLiveHere = {},
    std::vector<Item> itemsThatLiveHere = {})
{
    this->name = name;
    this->description = description;
    //this->neighbors = neighbors;
    this->peepsThatLiveHere = peepsThatLiveHere;
    this->itemsThatLiveHere = itemsThatLiveHere;
}

Location::Location() {

}

// Location::Location(std::string name, std::string description)
// {
//     this->name = name;
//     this->description = description;
// }


std::map<Direction, Location> Location::getNeighbors() { return this->neighbors; }

void Location::addLocation(Direction direction, Location location)
{
    // if (this->neighbors.find(direction) == this->neighbors.end()) {
    //     //Throw an exception here
    //     std::cout << "Something went wrong here" << std::endl;
    //     return;
    // }
    this->neighbors.insert(std::make_pair(direction, location));
}

void Location::addNPC(NPC npc) {
    this->peepsThatLiveHere.push_back(npc);
}

std::vector<NPC> Location::getNPCs()
{
    return this->peepsThatLiveHere;
}

void Location::addItem(Item item) {
    this->itemsThatLiveHere.push_back(item);
}

void Location::takeItem(Item item) {
    for (int i = 0; i < itemsThatLiveHere.size(); i++) {
        if (itemsThatLiveHere[i].getDescription() == item.getDescription()) {
            itemsThatLiveHere.erase(itemsThatLiveHere.begin() + i);
            return;
        }
    }

    std::cout << "Item " << item << " not removed from the world!" << std::endl;

}

std::vector<Item> Location::getItems() {
    return this->itemsThatLiveHere;
}

void Location::setVisit() {
    this->hasBeenVisited = true;
}

bool Location::getVisit()
{
    return this->hasBeenVisited;
}

std::string Location::getName()
{
    return this->name;
}


std::ostream & operator << (std::ostream &out, const Location &location) {
    out << location.name << " - " << location.description << std::endl << std::endl
        << "You see the following NPCs: " << std::endl;
    if (location.peepsThatLiveHere.size() > 0) {
        for (int i = 0; i < location.peepsThatLiveHere.size(); i++)
            out << "\t- " << location.peepsThatLiveHere[i] << std::endl;
    } else
        out << "There are no other people here. You are alone now..." << std::endl;

    out << std::endl << "You see the following items: " << std::endl;

    if (location.itemsThatLiveHere.size() > 0) {
        for (int j = 0; j < location.itemsThatLiveHere.size(); j++)
            out << "\t- " << location.itemsThatLiveHere[j] << std::endl;
    } else
        out << "There are no items here." << std::endl;

    out << std::endl << "You can go in the following directions:" << std::endl;

    if (location.neighbors.size() > 0) {
        for (auto item = location.neighbors.begin(); item != location.neighbors.end(); item++) {
            out << location.DirectionNames[item->first] << " - ";
            out << "Hase been visited" << item->second.hasBeenVisited << std::endl;
            if (!item->second.hasBeenVisited)
                out << item->second.name;
            else
                out <<  "Unknown";
            out << std::endl;
        }
    } else {
        out << "Where the hell even are we?" << std::endl;
    }

    return out;
}



