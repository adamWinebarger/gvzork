#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

class NPC {

public:
    //Constructor
    NPC(std::string name, std::string description, std::vector<std::string> messages);
    NPC(std::string name, std::string description);

    std::string getString(std::string which); //use input param to determine which string (description or name) we want to return
    std::string getCurrentNPCMessage();

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



#endif
