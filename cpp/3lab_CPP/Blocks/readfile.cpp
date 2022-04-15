#include "readfile.h"

#define MAKE_PROTOTYPE(TYPE) \
   Blocks* TYPE ## _myProtoype = \
      Blocks::addPrototype(#TYPE, new TYPE());

MAKE_PROTOTYPE(readfile)

int readfile::work(std::string data) {
    if(!Blocks::in_process)
        throw std::runtime_error("Workflow was executed :/\n");

    int i, p = 0;
    std::string check, name;

    for(i = 0; i < data.size(); ++i)
        if(data[i] == ' ') {
            std::copy(data.begin(), data.begin() + i, std::inserter(check, check.begin()));
            p = i + 1;
            i = 0;
            break;
        }
    if(i)
        std::copy(data.begin(), data.begin() + i, std::inserter(check, check.begin()));

    if(check != "readfile")
        throw std::runtime_error("Something went wrong :/\n");

    if(data.size() - p > 0)
        std::copy(data.begin() + p, data.end(), std::inserter(name, name.begin()));
    else
        throw std::runtime_error("There is no file name for readfile function\n");

    std::fstream from(name);

    if(!from)
        throw std::runtime_error("Unable to open the input file\n");

    std::string to_write;
    while(!from.eof()) {
        std::getline(from, to_write);
        Blocks::file.push_back(to_write);
    }
    from.close();

    return 0;
}




