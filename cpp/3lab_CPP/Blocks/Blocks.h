#ifndef INC_3LAB_C___BLOCKS_H
#define INC_3LAB_C___BLOCKS_H

#include <string>
#include <map>
#include <list>
#include <fstream>
#include <vector>
#include <algorithm>

class Blocks {
public:
    virtual ~Blocks() = default;
    virtual Blocks* clone() const = 0;
    virtual int work(std::string data);

    static Blocks* makeProduct(const std::string& type);
    static Blocks* addPrototype(const std::string& type, Blocks* p);

    static std::map<std::string, Blocks*> protoTable;
    static std::vector<std::string> file;
    static bool in_process;
};
#endif
