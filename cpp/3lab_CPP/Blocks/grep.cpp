#include "grep.h"

#define MAKE_PROTOTYPE(TYPE) \
   Blocks* TYPE ## _myProtoype = \
      Blocks::addPrototype(#TYPE, new TYPE());

MAKE_PROTOTYPE(grep)

int grep::work(std::string data) {
    if(!Blocks::in_process)
        throw std::runtime_error("Workflow was executed :/\n");

    int i, p = 0;
    std::string check, word;

    for(i = 0; i < data.size(); ++i)
        if(data[i] == ' ') {
            std::copy(data.begin(), data.begin() + i, std::inserter(check, check.begin()));
            p = i + 1;
            i = 0;
            break;
        }
    if(i)
        std::copy(data.begin(), data.begin() + i, std::inserter(check, check.begin()));

    if(check != "grep")
        throw std::runtime_error("Something went wrong :/\n");

    if(data.size() - p > 0)
        std::copy(data.begin() + p, data.end(), std::inserter(word, word.begin()));
    else
        throw std::runtime_error("There is no file word for readfile function\n");

    for(i = 0; i < Blocks::file.size(); ++i) {
        std::string s = Blocks::file[i];
        if (s.find(word) == std::string::npos)
            Blocks::file.erase(Blocks::file.begin() + i--);
    }

    return 0;
}