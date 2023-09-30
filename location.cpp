#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>

#include "direction.h"
#include "npc.hpp"
#include "item.h"

class Location {

public:

    //Constructor
    Location(std::string name, std::string description, std::vector<NPC> peepsThatLiveHere,
             std::vector<Item> itemsThatLiveHere, std::map<Direction, Location> neighbors);
    Location(std::string name, std::string description);

    //Getter for the neighbors
    std::map<Direction, Location> getNeighbors();

    void setVisit(bool Value);
    bool getVisit();

    void addLocation(Direction direction, Location location);
    void addNPC(NPC npc);
    void addItem(Item item);

    std::vector<NPC> getNPCs();
    std::vector<Item> getItems();

    friend std::ostream & operator << (std::ostream &out, const Location &location);

private:
    std::string name, description;
    bool hasBeenVisited = false;
    std::map<Direction, Location> neighbors;
    std::vector<NPC> peepsThatLiveHere;
    std::vector<Item> itemsThatLiveHere;
    std::string DirectionNames[11] = { "North", "Northeast", "East", "Southeast", "South",
         "Southwest", "West", "Northwest", "Secret", "Portal", "Portal"};
};

Location::Location(std::string name, std::string description, std::vector<NPC> peepsThatLiveHere = {},
             std::vector<Item> itemsThatLiveHere = {}, std::map<Direction, Location> neighbors = {})
{
    this->name = name;
    this->description = description;
    this->neighbors = neighbors;
    this->peepsThatLiveHere = peepsThatLiveHere;
    this->itemsThatLiveHere = itemsThatLiveHere;
}


std::map<Direction, Location> Location::getNeighbors() { return this->neighbors; }

void Location::addLocation(Direction direction, Location location)
{
    if (this->neighbors.find(direction) == this->neighbors.end()) {
        //Throw an exception here

        return;
    }
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

std::vector<Item> Location::getItems() {
    return this->itemsThatLiveHere;
}

void Location::setVisit(bool Value) {
    this->hasBeenVisited = Value;
}

bool Location::getVisit()
{
    return this->hasBeenVisited;
}

std::ostream & operator << (std::ostream &out, const Location &location) {
    out << location.name << " - " << location.description << std::endl << std::endl
        << "You see the following NPCs: " << std::endl;

    for (int i = 0; i < location.peepsThatLiveHere.size(); i++)
        out << "\t- " << location.peepsThatLiveHere[i] << std::endl;

    out << std::endl << "You see the following items: " << std::endl;

    for (int j = 0; j < location.itemsThatLiveHere.size(); j++)
        out << "\t- " << location.itemsThatLiveHere[j] << std::endl;

    out << std::endl << "You can go in the following directions:" << std::endl;

    if (location.neighbors.size() > 0) {
        for (auto item = location.neighbors.begin(); item != location.neighbors.end(); item++) {
            out << location.DirectionNames[item->first] << " - ";
            (item->second.hasBeenVisited) ? out << item->second.description : out << "Unknown";
        }
    } else {
        out << "Where the hell even are we?" << std::endl;
    }

    return out;
}




