#include "sort.h"

#define MAKE_PROTOTYPE(TYPE) \
   Blocks* TYPE ## _myProtoype = \
      Blocks::addPrototype(#TYPE, new TYPE());

MAKE_PROTOTYPE(sort)

int sort::work(std::string data) {
    if(!Blocks::in_process)
        throw std::runtime_error("Workflow was executed :/\n");

    int i, p = 0;
    std::string check, word;

    std::copy(data.begin(), data.end(), std::inserter(check, check.begin()));

    if(check != "sort")
        throw std::runtime_error("Something went wrong :/\n");

    std::sort(Blocks::file.begin(), Blocks::file.end());

    return 0;
}