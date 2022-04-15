#ifndef INC_3LAB_C___PARSER_H
#define INC_3LAB_C___PARSER_H

#include <list>
#include <string>
#include <map>
#include <fstream>

class Parser {
private:
    std::list<std::string> from;
    std::list<std::string> desc;
    std::string str;

public:
    std::map <int, std::string> blocks;
    std::list<int> chain;

    int getData(char *path);
    int parseData();
    int parseDesc();
    int parseChain();
    int general(char *path);

};

#endif
