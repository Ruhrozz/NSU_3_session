#include "Blocks.h"

std::map<std::string, Blocks*> Blocks::protoTable;
std::vector<std::string> Blocks::file;
bool Blocks::in_process = true;

Blocks * find(const std::string& name, std::map<std::string, Blocks*> protoTable) {
    return protoTable[name];
}


Blocks* Blocks::makeProduct(const std::string& type)
{
    Blocks *proto = find(type, protoTable);

    if(proto == nullptr)
        throw std::runtime_error("Function not found\n");

    return proto->clone();
}


Blocks* Blocks::addPrototype(const std::string& type, Blocks* p)
{
    Blocks::in_process = true;
    protoTable[type] = p;
    return p;
}

int Blocks::work(std::string data) {
    return 0;
}
