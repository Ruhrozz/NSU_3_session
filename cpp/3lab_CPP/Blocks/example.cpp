#include "example.h"

#define MAKE_PROTOTYPE(TYPE) \
   Blocks* TYPE ## _myProtoype = \
      Blocks::addPrototype(#TYPE, new TYPE());

MAKE_PROTOTYPE(example)

int example::work(std::string data) {
    return 0;
}