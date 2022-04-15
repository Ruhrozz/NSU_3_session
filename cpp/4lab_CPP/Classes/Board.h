#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include <iostream>
#include <map>
#include "Figure.h"

class Board {
public:
    static void print_board(const std::map <std::string, Figure*> &pos);
    static void print_win();
    static void print_draw();
};


#endif
