#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <string>
#include <stdexcept>

class item{
        public:
                item();
                //// Constructor to initialize the attributes
                item(std::string name,std::string description, int calories, int weight);

                //accessors
                std::string getName();
                std::string getDescription();
                int getCalories();
                int getWeight();

                //setters
                void setName(std::string name);
                void setDescription(std::string description);
                void setCalories(int calories);
                void setWeight(int weight);

        private:
                std::string name;
                std::string description;
                int calories;
                int weight;
};
#endif // ITEM_H
