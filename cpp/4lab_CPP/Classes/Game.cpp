#include "Game.h"

Game::Game() {
    mv = 0;
    char a[][24] = {"a1", "a3", "b2", "c1", "c3", "d2", "e1", "e3", "f2", "g1", "g3", "h2",
                    "a7", "b6", "b8", "c7", "d6", "d8", "e7", "f6", "f8", "g7", "h6", "h8"};
    for(int i = 0; i < 24; ++i) {
        if(i < 12)
            pos[a[i]] = new Figure(0);
        else
            pos[a[i]] = new Figure(1);
    }
}

std::map<std::string, Figure *> Game::get_pos() {
    return pos;
}

int Game::get_mv() const {
    return mv;
}

int Game::move(const std::vector<std::string>& turn, int act) {
    if(act == 0)
        return 1;

    if(act == 1) {
        pos[turn[1]] = pos[turn[0]];

        auto it = pos.find(turn[0]);
        pos.erase(it);

        mv = (mv + 1) % 2;

        find_dam();
        return 0;
    }

    if(act == 2) {
        int g = eat(turn);
        find_dam();
        return g;
    }

    return 666;
}

int Game::eat(const std::vector<std::string> &turn) {
    std::string del = "xx";
    del[0] = (char) ((turn[0][0] + turn[1][0]) / 2);
    del[1] = (char) ((turn[0][1] + turn[1][1]) / 2);

    delete pos[del];
    pos.erase(del);

    pos[turn[1]] = pos[turn[0]];
    auto it = pos.find(turn[0]); // Deleting a checker
    pos.erase(it);

    if(!to_eat(turn[1]))
        mv = (mv + 1) % 2;
    else
        return 1;
    return 0;
}

int Game::win() {
    int count_white = 0;
    int count_black = 0;
    for(auto& i : pos) {
        if (i.second->color == 0)
            ++count_white;
        else
            ++count_black;
    }
    if(count_black == 0 or count_white == 0)
        return 1;
    return 0;
}

void Game::whose_turn() const {
    if(mv == 0)
        std::cout << "=====White's turn=====" << std::endl;
    else
        std::cout << "                      =====Black's turn=====" << std::endl;
}

int Game::to_eat(const std::string& str) {
    must.clear();
    for (auto &item: pos) {
        if (item.first != str)
            continue;

        std::string enemy = "xx";
        std::string position = item.first;

        for(int i = -1; i < 2; i += 2) {
            for(int j = -1; j < 2; j += 2) {
                enemy[0] = (char) (position[0] + i);
                enemy[1] = (char) (position[1] + j);

                const auto found1 = pos.find(enemy);
                if(found1!=pos.cend() and pos[enemy]->color != mv) {
                    enemy[0] = (char) (enemy[0] + i);
                    enemy[1] = (char) (enemy[1] + j);

                    const auto found2 = pos.find(enemy);
                    if(found2==pos.cend())
                        if(enemy[0] >= 'a' and enemy[0] <= 'h'
                           and enemy[1] >= '1' and enemy[1] <= '8')
                            must.emplace_back(position, enemy);
                }
            }
        }
    }
    if(must.empty())
        return 0;
    else
        return 1;
}

int Game::find_dam() {
    for(auto& item : pos) {
        if(item.first[1] == '8' and item.second->color == 0 and item.second->dam != 1)
            item.second->dam = 1;
        if(item.first[1] == '1' and item.second->color == 1 and item.second->dam != 1)
            item.second->dam = 1;
    }
    return 0;
}
