#include "Player.h"


int Player::make_move(const std::map <std::string, Figure*> &pos, int bot, int color) {
    turn.clear();

    analyse(pos, color);

    if(must.empty() and possible.empty())
        return 3;

    std::string str1, str2;

    if (bot) {
        std::random_device rd;
        std::mt19937 mersenne(rd());
        unsigned int t = mersenne();

        if (must.empty()) {
            t %= possible.size();
            turn.push_back(possible[t].first);
            turn.push_back(possible[t].second);
            return 1;
        } else {
            t %= must.size();
            turn.push_back(must[t].first);
            turn.push_back(must[t].second);
            return 2;
        }
    } else
        std::cin >> str1 >> str2;

    if (must.empty()) {
        for (auto &i: possible)
            if (i.first == str1 and i.second == str2) {
                turn.push_back(str1);
                turn.push_back(str2);
                return 1;
            }
        std::cout << "This move doesn't exist." << std::endl;
    } else {
        for (auto &i: must)
            if (i.first == str1 and i.second == str2) {
                turn.push_back(str1);
                turn.push_back(str2);
                return 2;
            }
        std::cout << "You can't. You have to eat." << std::endl;
    }

    return 0;
}

int Player::analyse(const std::map<std::string, Figure *>& pos, int color) {
    must.clear();
    possible.clear();

    to_eat(pos, color);
    to_move(pos, color);

    return 0;
}

int Player::to_eat(std::map<std::string, Figure *> pos, int color) {
    for (auto &item: pos) {
        if (item.second->color != color)
            continue;

        std::string enemy = "xx";
        std::string position = item.first;

        for(int i = -1; i < 2; i += 2) {
            for(int j = -1; j < 2; j += 2) {
                enemy[0] = (char) (position[0] + i);
                enemy[1] = (char) (position[1] + j);

                const auto found1 = pos.find(enemy);
                if(found1!=pos.cend() and pos[enemy]->color != color) {
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
    return 0;
}

int Player::to_move(std::map<std::string, Figure *> pos, int color) {
    for(auto& item : pos) {
        if(item.second->color != color)
            continue;

        std::string empty = "xx";
        std::string position = item.first;
        if(color == 0 or item.second->dam == 1)
            if(position[0] != 'a' and position[1] != '8') {
                empty[0] = (char) (position[0] - 1);
                empty[1] = (char) (position[1] + 1);

                const auto found1 = pos.find(empty);
                if(found1==pos.cend())
                    possible.emplace_back(position, empty);
            }
        if(color == 0 or item.second->dam == 1)
            if(position[0] != 'h' and position[1] != '8') {
                empty[0] = (char) (position[0] + 1);
                empty[1] = (char) (position[1] + 1);

                const auto found1 = pos.find(empty);
                if(found1==pos.cend())
                    possible.emplace_back(position, empty);
            }

        if(color == 1 or item.second->dam == 1)
            if(position[0] != 'h' and position[1] != '1') {
                empty[0] = (char) (position[0] + 1);
                empty[1] = (char) (position[1] - 1);

                const auto found1 = pos.find(empty);
                if(found1==pos.cend())
                    possible.emplace_back(position, empty);
            }

        if(color == 1 or item.second->dam == 1)
            if(position[0] != 'a' and position[1] != '1') {
                empty[0] = (char) (position[0] - 1);
                empty[1] = (char) (position[1] - 1);

                const auto found1 = pos.find(empty);
                if(found1==pos.cend())
                    possible.emplace_back(position, empty);
            }
    }
    return 0;
}

std::vector<std::string> Player::get_turn() {
    return turn;
}

