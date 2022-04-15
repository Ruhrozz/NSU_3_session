#ifndef INC_3LAB_C___EXAMPLE_H
#define INC_3LAB_C___EXAMPLE_H


#include "Blocks.h"

#define IMPLEMENT_CLONE(TYPE) \
   replace* clone() const { return new TYPE(*this); }

class replace: public Blocks {
public:
    IMPLEMENT_CLONE(replace);
    virtual int work(std::string data);
    static std::string ReplaceString(std::string subject,
                                     const std::string& search,
                                     const std::string& replace);
};


#endif
