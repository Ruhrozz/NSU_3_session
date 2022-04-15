#ifndef INC_3LAB_C___EXAMPLE_H
#define INC_3LAB_C___EXAMPLE_H


#include "Blocks.h"

#define IMPLEMENT_CLONE(TYPE) \
   dump* clone() const { return new TYPE(*this); }

class dump: public Blocks {
public:
    IMPLEMENT_CLONE(dump);
    virtual int work(std::string data);
};


#endif
