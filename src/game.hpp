#if !defined(TIC_TAC_TOE_GAME_HPP)
#define TIC_TAC_TOE_GAME_HPP

#include "board.hpp"

namespace tic_tac_toe {
    
class game {
private:
    int m_move;
    bool m_player_move;

    int negamax(
        board *node,
        int depth,
        int alpha,
        int beta,
        int color,
        int player);

public:
    game();

    board m_board;

    void reset();

    bool is_over();
    bool is_player_move();

    bool make_move(size_t row, size_t col);
    bool computer_move();

    void display();
};

} // namespace tic_tac_toe


#endif // TIC_TAC_TOE_GAME_HPP
