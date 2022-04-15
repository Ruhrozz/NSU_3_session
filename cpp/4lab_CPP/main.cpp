#include "Classes/Controller.h"

int main() {
    char j = 'x';
    std::cout << "If Player vs Player, print 0, if Player vs Bot, print 1, if Bot vs Bot, print 2" << std::endl;
    while(j != '1' and j != '0' and j != '2') {
        std::cin >> j;
        if (j == '2')
            Controller::start(2);
        else if (j == '1')
            Controller::start(1);
        else if (j == '0')
            Controller::start(0);
        else
            std::cout << "Again." << std::endl;
    }
    return 0;
}
