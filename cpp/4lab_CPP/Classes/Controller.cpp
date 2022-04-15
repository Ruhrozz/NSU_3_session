#include "Controller.h"

void Controller::start(int bot) {
    Game game;
    Player player;

    while(!game.win()) {
        system("clear");
        Board::print_board(game.get_pos());
        game.whose_turn();
        std::cout << "  Advice: Enter the move like \"a3 b4\"\n";
        int i = 0;
        if(bot == 2)
            i = 1;
        for(; i < bot + 1; ++i) {
            int act = 1;
            do {
                if(act != 0) {
                    system("clear");
                    Board::print_board(game.get_pos());
                    game.whose_turn();
                    system("sleep 1");
                }
                act = player.make_move(game.get_pos(), i, game.get_mv());
                if(act == 3) {
                    Board::print_draw();
                    return;
                }
            } while (game.move(player.get_turn(), act));
        }
    }

    system("clear");
    Board::print_board(game.get_pos());
    Board::print_win();
}