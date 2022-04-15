#ifndef INC_3LAB_C___EXAMPLE_H
#define INC_3LAB_C___EXAMPLE_H


#include "Blocks.h"

#define IMPLEMENT_CLONE(TYPE) \
   sort* clone() const { return new TYPE(*this); }

class sort: public Blocks {
public:
    IMPLEMENT_CLONE(sort);
    virtual int work(std::string data);
};


#endif
