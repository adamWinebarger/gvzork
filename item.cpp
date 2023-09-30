#include "item.h"
#include <iostream>
#include <string>
#include <cstdlib> // Include this if you need string-to-integer conversions

// Constructor to initialize the attributes
item::item(std::string name, std::string description, int calories, int weight){
        this->name = name;
        this->description = description;
        this->calories = calories;
        this->weight = weight;
}

// Accessors
std::string item::getName() {
        return name;
}

std::string item::getDescription() {
        return description;
}

int item::getCalories() {
        return calories;
}

int item::getWeight() {
        return weight;
}

// Setters
void item::setName(std::string name) {
        if (name.empty()) {
                throw std::invalid_argument("Having no name is not permitted");
        }
        this->name = name;
}

void item::setDescription(std::string description) {
        if (description.empty()) {
                throw std::invalid_argument("Item needs description!");
        }
        this->description = description;
}

void item::setCalories(int calories) {
        if (calories < 0 || calories > 1000) {
                throw std::out_of_range("Calories must be between 0 and 1000.");
        }
        this->calories = calories;
}
//just noticed this needs to be a float will fix later
void item::setWeight(int weight) {
        if (weight < 0.0 || weight > 500.0) {
                throw std::out_of_range("Weight must be between 0 and 500.");
        }
        this->weight = weight;
}
