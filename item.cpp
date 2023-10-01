#include <iostream>
#include <string>
#include <cstdlib> // Include this if you need string-to-integer conversions
#include <stdexcept>

class Item{
public:
        //item(); //We might not need the default if our values have to be initialized. If you want to leave it in, then we should pre-initialize our variables for default constructors
        //// Constructor to initialize the attributes
        Item(std::string name,std::string description, float weight = 0.0, int calories = 0);

        //accessors
        std::string getName();
        std::string getDescription();
        int getCalories();
        float getWeight();

        //setters
        void setName(std::string name);
        void setDescription(std::string description);
        void setCalories(int calories);
        void setWeight(float weight);

        //ostream operator that returns the name of the NPC

        /*
                So, looking over the documentation and the geeksforgeeks tutorial shit, it looks like by overloading the ostream
                operator in this way, it sets it up so that we could do something like

                Item item("banana", "orange");
                cout << item << endl;

                and that will print out the item name... so that's pretty neat. Did we cover this in class that day that I was zoned out?
        */

        friend std::ostream & operator << (std::ostream &out, const Item &item);

private:
        std::string name;
        std::string description;
        int calories;
        float weight;
};

// Constructor to initialize the attributes
Item::Item(std::string name, std::string description, float weight, int calories){
        this->name = name;
        this->description = description;
        this->calories = calories;
        this->weight = weight;
}

// Accessors
std::string Item::getName() {
        return name;
}

std::string Item::getDescription() {
        return description;
}

int Item::getCalories() {
        return calories;
}

float Item::getWeight() {
        return weight;
}

// Setters

//So we might be able to get away with no
void Item::setName(std::string name) {
        if (name.empty()) {
                throw std::invalid_argument("Having no name is not permitted");
        }
        this->name = name;
}

void Item::setDescription(std::string description) {
        if (description.empty()) {
                throw std::invalid_argument("Item needs description!");
        }
        this->description = description;
}

void Item::setCalories(int calories) {
        if (calories < 0 || calories > 1000) {
                throw std::out_of_range("Calories must be between 0 and 1000.");
        }
        this->calories = calories;
}
//Fixed it for you
void Item::setWeight(float weight) {
        if (weight < 0.0 || weight > 500.0) {
                throw std::out_of_range("Weight must be between 0 and 500.");
        }
        this->weight = weight;
}

std::ostream & operator << (std::ostream &out, const Item &item) {
        out << item.name << "(" << item.calories << " calories) - " << item.weight << " lb - " << item.description << std::endl;
        return out;
}
