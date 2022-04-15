#ifndef INC_3LAB_C___EXAMPLE_H
#define INC_3LAB_C___EXAMPLE_H


#include "Blocks.h"

#define IMPLEMENT_CLONE(TYPE) \
   grep* clone() const { return new TYPE(*this); }

class grep: public Blocks {
public:
    IMPLEMENT_CLONE(grep);
    virtual int work(std::string data);
};


#endif
