#include <iostream>
#include <string>
#include <vector>

#include "item.h" // Include the item header file
#include "npc.hpp"
#include "direction.h"
#include "location.hpp"

// as of right now here to test item

using namespace std; //we're doing this so I don't have to type a bunch of std shit over and over again

int main() {
        // Create an item object and initialize its attributes
        Item item1("Apple", "It's a red apple", 95, 2);
        NPC npc1("Gnome A", "A simple gnome, eh?",
                {"How do you do?", "I'm a simple Gnome", "I don't have a name yet. But maybe I'll get one soon", "Have a nice day"}
        );
        NPC npc2("Ant A", "A nameless giant ant");//,
        //{"sktt sktt sktt", "skitter skitter", "I'm just kidding. I can understand you"}
        //);
        Item item2("Book", "its a large book", 0, 10);
        // item item3("pizza","food",220,20);
        // // You can now use the accessors to retrieve information about the item
        // std::cout << "Name: " << item1.getName() << std::endl;
        // std::cout << "Description: " << item1.getDescription() << std::endl;
        // std::cout << "Calories: " << item1.getCalories() << std::endl;
        // std::cout << "Weight: " << item1.getWeight() << std::endl;
        // //item 2
        // std::cout << "Name: " << item2.getName() << std::endl;
        // std::cout << "Description: " << item2.getDescription() << std::endl;
        // std::cout << "Calories: " << item2.getCalories() << std::endl;
        // std::cout << "Weight: " << item2.getWeight() << std::endl;
        // //item3
        // std::cout << "Name: " << item3.getName() << std::endl;
        // std::cout << "Description " << item3.getDescription() << std::endl;
        // std::cout << "Calories: " << item3.getCalories() << std::endl;
        // std::cout << "Weight: " << item3.getWeight() << std::endl;

        cout << npc1 << endl;
        //cout << npc1 << endl;

        do {
               cout << npc1.getCurrentNPCMessage() << endl;
        } while (npc1.getMessageNumber() != 0);

        Direction d = East;
        cout << d << endl;

        Location l("The b's", "This is a starter location");
        cout << l << endl;


        //cin.get();
        return 0;
}
