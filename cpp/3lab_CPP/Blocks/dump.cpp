#include "dump.h"

#define MAKE_PROTOTYPE(TYPE) \
   Blocks* TYPE ## _myProtoype = \
      Blocks::addPrototype(#TYPE, new TYPE());

MAKE_PROTOTYPE(dump)

int dump::work(std::string data) {
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

    if(check != "writefile")
        throw std::runtime_error("Something went wrong :/\n");

    if(data.size() - p > 0)
        std::copy(data.begin() + p, data.end(), std::inserter(name, name.begin()));
    else
        throw std::runtime_error("There is no file name for writefile function\n");

    std::ofstream out(name);

    if(!out)
        throw std::runtime_error("Unable to open the output file\n");

    std::string to_write;

    for(i = 0; i < Blocks::file.size(); ++i) {
        out << Blocks::file[i] << std::endl;
    }

    out.close();

    return 0;
}