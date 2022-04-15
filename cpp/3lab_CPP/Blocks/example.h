#ifndef INC_3LAB_C___EXAMPLE_H
#define INC_3LAB_C___EXAMPLE_H


#include "Blocks.h"

#define IMPLEMENT_CLONE(TYPE) \
   example* clone() const { return new TYPE(*this); }

class example: public Blocks {
public:
    IMPLEMENT_CLONE(example);
    virtual int work(std::string data);
};


#endif
