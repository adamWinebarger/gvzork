#include "item.h" // Include the item header file
#include <iostream>
#include <string>
// as of right now here to test item
int main() {
        // Create an item object and initialize its attributes
        item item1("Apple", "It's a red apple", 95, 2);
        item item2("Book", "its a large book", 0, 10);
        item item3("pizza","food",220,20);
        // You can now use the accessors to retrieve information about the item
        std::cout << "Name: " << item1.getName() << std::endl;
        std::cout << "Description: " << item1.getDescription() << std::endl;
        std::cout << "Calories: " << item1.getCalories() << std::endl;
        std::cout << "Weight: " << item1.getWeight() << std::endl;
        //item 2
        std::cout << "Name: " << item2.getName() << std::endl;
        std::cout << "Description: " << item2.getDescription() << std::endl;
        std::cout << "Calories: " << item2.getCalories() << std::endl;
        std::cout << "Weight: " << item2.getWeight() << std::endl;
        //item3
        std::cout << "Name: " << item3.getName() << std::endl;
        std::cout << "Description " << item3.getDescription() << std::endl;
        std::cout << "Calories: " << item3.getCalories() << std::endl;
        std::cout << "Weight: " << item3.getWeight() << std::endl;
        return 0;
}
