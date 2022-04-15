#ifndef UNTITLED_PRODUCT1_H
#define UNTITLED_PRODUCT1_H


#include "Blocks.h"

#define IMPLEMENT_CLONE(TYPE) \
   readfile* clone() const { return new TYPE(*this); }

class readfile: public Blocks {
public:
    IMPLEMENT_CLONE(readfile);
    virtual int work(std::string data);
};


#endif
