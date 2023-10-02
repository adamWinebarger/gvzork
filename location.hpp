#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>

#include "direction.h"
#include "npc.hpp"
#include "item.h"

class Location {
private:
    std::string name, description;
    bool hasBeenVisited = false;
    std::map<Direction, Location> neighbors = {};
    std::vector<NPC> peepsThatLiveHere = {};
    std::vector<Item> itemsThatLiveHere = {};
    std::string DirectionNames[11];

public:

    //Constructor
    Location(std::string name, std::string description, std::vector<NPC> peepsThatLiveHere = {},
             std::vector<Item> itemsThatLiveHere = {});
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

    std::string getName();

    std::vector<NPC> getNPCs();
    std::vector<Item> getItems();

    friend std::ostream & operator << (std::ostream &out, const Location location);

};

#endif
