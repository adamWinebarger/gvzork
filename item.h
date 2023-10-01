#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <stdexcept>

class Item{
public:
        //item(); //We might not need the default if our values have to be initialized. If you want to leave it in, then we should pre-initialize our variables for default constructors
        //// Constructor to initialize the attributes
        Item(std::string name,std::string description,float weight = 0.0, int calories = 0);

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

#endif // ITEM_H
