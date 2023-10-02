#include <iostream>
#include <vector>
#include <cstdlib>

class NPC {
public:
    //Constructor
    NPC(std::string name, std::string description, std::vector<std::string> messages);
    NPC(std::string name, std::string description);

    //use input param to determine which string (description or name) we want to return
    std::string getString(std::string which);

    std::string getCurrentNPCMessage();

    //We may want to build this out a bit. But this will do for now
    void loadNPCsMessages(std::vector<std::string> messages);

    int getMessageNumber();

    std::string getName();
    std::string getDescription();

    friend std::ostream & operator << (std::ostream &out, const NPC &npc);
    bool operator == (const std::string &rhs);

private:
    std::string name, description;
    int messageNumber = 0;
    std::vector<std::string> messages;
};

//Constructors
NPC::NPC(std::string name, std::string description, std::vector<std::string> messages) {
    this->name = name;
    this->description = description;
    this->messages = messages;
}

NPC::NPC(std::string name, std::string description) {
    this->name = name;
    this->description = description;
}

//use input param to determine which string (description or name) we want to return
std::string NPC::getString(std::string which) {
    if (which == "name")
        return this->name;
    else if (which == "description")
        return this->description;
    else
        return "I'm not sure what you want me to give you";
}

std::string NPC::getCurrentNPCMessage() {
    if (messageNumber == messages.size() -1 ) {
        this->messageNumber = 0;
        return messages[messages.size() - 1];
    }
    else
        return messages[messageNumber++];
}

//We may want to build this out a bit. But this will do for now
void NPC::loadNPCsMessages(std::vector<std::string> messages) {
    this->messages = messages;
}

int NPC::getMessageNumber() {
    return this->messageNumber;
}

std::string NPC::getName() {
    return this->name;
}

std::string NPC::getDescription() {
    return this->description;
}

//here's our little overload operator.
std::ostream & operator << (std::ostream &out, const NPC &npc) {
 out << npc.name << std::endl;
 return out;
}

bool NPC::operator == (const std::string &rhs) {
    return this->name == rhs;
}
