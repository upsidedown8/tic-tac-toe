#include <iostream>
#include "game.hpp"

int main(int argc, char **argv) {
    tic_tac_toe::game game;
    int row, col;

    while (!game.is_over()) {
        // system("clear");
        if (game.is_player_move()) {
            game.display();
            while (game.is_player_move()) { 
                std::cout << "enter row: ";
                std::cin >> row;
                std::cout << "enter col: ";
                std::cin >> col;

                if (game.make_move(row, col))
                    break;

                std::cout << "failed to move, try again" << std::endl;
            }
            std::cout << std::endl;
        } else {
            game.computer_move();
        }
    }
    game.display();

    return 0;
}
