#ifndef CHECKERS_GAME_H
#define CHECKERS_GAME_H

#include "Figure.h"
#include <vector>
#include <algorithm>
#include <map>

class Game {
private:
    int mv;
    std::map <std::string, Figure*> pos;
    std::vector<std::pair<std::string, std::string>> must;
public:
    Game();
    int get_mv() const;
    std::map <std::string, Figure*> get_pos();
    int move(const std::vector <std::string>& turn, int act);
    int to_eat(const std::string& str);
    int eat(const std::vector <std::string>& turn);
    int win();
    int find_dam();
    void whose_turn() const;
};


#endif
