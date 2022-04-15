#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include "Figure.h"

class Player {
private:
    std::vector <std::string> turn;
    std::vector<std::pair<std::string, std::string>> must;
    std::vector<std::pair<std::string, std::string>> possible;
public:
    std::vector <std::string> get_turn();
    int to_eat(std::map<std::string, Figure *> pos, int color);
    int to_move(std::map<std::string, Figure *> pos, int color);
    int analyse(const std::map <std::string, Figure*>& pos, int color);
    int make_move(const std::map <std::string, Figure*> &pos, int bot, int color);
};


#endif
