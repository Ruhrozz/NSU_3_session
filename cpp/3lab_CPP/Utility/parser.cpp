#include "parser.h"


int Parser::getData(char *path) {
    std::string s;
    std::ifstream in(path);

    while(getline(in, s))
        from.push_back(s);

    in.close();

    return 0;
}


int Parser::parseData() {
    std::string s;

    if(!from.empty()) {
        s = from.front();
        from.pop_front();
    } else
        throw std::runtime_error("Not enough data\n");

    if(s == "desc") {
        while(true) {
            if(!from.empty()) {
                s = from.front();
                from.pop_front();
            } else
                throw std::runtime_error("File doesn't have \"csed\" option\n");
            if(s == "csed")
                break;
            desc.push_back(s);
        }
    } else
        throw std::runtime_error("File doesn't have \"desc\" option\n");

    if(!from.empty()) {
        s = from.front();
        from.pop_front();
    } else
        throw std::runtime_error("File doesn't have line of blocks\n");

    str = s;

    return 0;
}


// Source: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


int Parser::parseDesc() {
    int i;

    while(!desc.empty()) {
        std::string s, b_name, b_func;

        s = desc.front();
        desc.pop_front();

        for(i = 0; i < s.size() and s[i] != ' '; ++i);

        if(i == 0 or i + 4 > s.size())
            throw std::runtime_error("Bad block's structure: something bad with name. Maybe one is missing\n");
        if(s[i] != ' ' or s[i+1] != '=' or s[i+2] != ' ')
            throw std::runtime_error("Bad block's structure: something wrong with \'=\' operator\n");

        std::copy(s.begin(), s.begin() + i, std::inserter(b_name, b_name.begin()));
        std::copy(s.begin() + i + 3, s.end(), std::inserter(b_func, b_func.begin()));

        if(!is_number(b_name))
            throw std::runtime_error("Bad block's structure: name of the block is not a digit number\n");

        blocks[std::stoi(b_name)] = b_func;
    }
    return 0;
}


int Parser::parseChain() {
    int i, p;

    for(i = 0, p = 0; i < str.size(); ++i) {
        if(str[i] == ' ') {
            std::string s;
            std::copy(str.begin() + p, str.begin() + i, std::inserter(s, s.begin()));
            if(is_number(s))
                chain.push_back(std::stoi(s));
            else
                throw std::runtime_error("Describing structure's scheme has block which name has not only digits\n");
            if(i + 3 < str.size() and str[i+1] == '-' and str[i+2] == '>' and str[i+3] == ' ')
                p = i = i + 4;
            else
                throw std::runtime_error("Describing structure's scheme has problems with operator \'->\' or redundant spaces\n");

        }
    }

    if(i != p) {
        std::string s;
        std::copy(str.begin() + p, str.begin() + i, std::inserter(s, s.begin()));
        if(is_number(s))
            chain.push_back(std::stoi(s));
        else
            throw std::runtime_error("Describing structure's scheme has block which name has not only digits\n");
    }
    return 0;
}


int Parser::general(char *path) {
    getData(path);
    parseData();
    parseDesc();
    parseChain();
    return 0;
}


