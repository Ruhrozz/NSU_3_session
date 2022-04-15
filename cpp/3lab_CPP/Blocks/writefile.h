#ifndef INC_3LAB_C___WRITEFILE_H
#define INC_3LAB_C___WRITEFILE_H


#include "Blocks.h"

#define IMPLEMENT_CLONE(TYPE) \
   writefile* clone() const { return new TYPE(*this); }

class writefile: public Blocks {
public:
    IMPLEMENT_CLONE(writefile);
    virtual int work(std::string data);
};


#endif