#include "Board.h"

void Board::print_board(const std::map <std::string, Figure*> &pos) {
    int board [8][8];

    /* Positions of all Figures to 8x8 matrix
     * -1: the absence of Figure
     *  0: White Figure
     *  1: Black Figure
     * 10: White Dam
     * 11: Black Dam                       */

    for(auto & i : board)
        for(int & j : i)
            j = -1;

    auto it = pos.begin();
    for(int i = 0; it != pos.end(); it++, i++) {
        char fst_letter = it->first[0], fst_digit = it->first[1];
        int fl, fd;
        fl = fst_letter - 97;
        fd = fst_digit - 49;
        board[fl][fd] = it->second->color + 10 * it->second->dam;
    }


    /* Printing the board depending on matrix
     * O: White standard Figure
     * X: Black standard Figure
     * @: White dam Figure
     * #: Black dam Figure                  */

    std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
    for(int i = 7; i >= 0; --i) {
        std::cout<< i + 1 << " | ";
        for (auto & j : board) {
            if(j[i] == 0)
                std::cout << "O | ";
            else if(j[i] == 10)
                std::cout << "@ | ";
            else if(j[i] == 1)
                std::cout << "X | ";
            else if(j[i] == 11)
                std::cout << "% | ";
            else
                std::cout << "  | ";
        }
        std::cout << std::endl;
        std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
    }
    std::cout << "    a   b   c   d   e   f   g   h  " << std::endl << std::endl;
}


void Board::print_win() {
    std::cout << "Congratulations!\n";
    std::cout << "Congratulations!!\n";
    std::cout << "Congratulations!!!\n";
}

void Board::print_draw() {
    std::cout << "That's a draw...\n";
    print_win();
}
