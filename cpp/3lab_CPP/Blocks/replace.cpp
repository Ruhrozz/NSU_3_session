#include "replace.h"

#define MAKE_PROTOTYPE(TYPE) \
   Blocks* TYPE ## _myProtoype = \
      Blocks::addPrototype(#TYPE, new TYPE());

MAKE_PROTOTYPE(replace)

std::string replace::ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

int replace::work(std::string data) {
    if(!Blocks::in_process)
        throw std::runtime_error("Workflow was executed :/\n");

    int i, p = 0;
    std::string check, word1, word2;

    for(i = 0; i < data.size(); ++i)
        if(data[i] == ' ') {
            std::copy(data.begin(), data.begin() + i, std::inserter(check, check.begin()));
            p = i + 1;
            i = 0;
            break;
        }
    if(i)
        std::copy(data.begin(), data.begin() + i, std::inserter(check, check.begin()));

    if(check != "replace")
        throw std::runtime_error("Something went wrong :/\n");

    for(i = p; i < data.size(); ++i)
        if (data[i] == ' ') {
            std::copy(data.begin() + p, data.begin() + i, std::inserter(word1, word1.begin()));
            p = i + 1;
            i = 0;
            break;
        }
    if(i)
        throw std::runtime_error("Too few arguments or spaces\n");
    std::copy(data.begin() + p, data.end(), std::inserter(word2, word2.begin()));
    if(word2 == "")
        throw std::runtime_error("Too few arguments\n");
    if(word2.find(' ') != std::string::npos)
        throw std::runtime_error("Too many arguments or spaces\n");

    for(i = 0; i < Blocks::file.size(); ++i)
        Blocks::file[i] = ReplaceString(Blocks::file[i], word1, word2);

    return 0;
}