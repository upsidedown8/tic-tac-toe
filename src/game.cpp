#include "game.hpp"

#include <algorithm>
#include <cstdio>

int tic_tac_toe::game::negamax(
    board *node,
    int depth,
    int alpha,
    int beta,
    int color,
    int player) {
        int value = node->evaluate();
        if (depth == 0 || value != INDETERMINATE)
            return color * value * 10 + color * depth;

        value = -2;
        int_fast32_t pos = 1;
        for (size_t i = 0; i < 9; i++, pos <<= 1) {
            if (!node->is_occupied(pos)) {
                node->set(pos, player);
                value = std::max(value, -negamax(
                    node,
                    depth - 1,
                    -beta,
                    -alpha,
                    -color,
                    player == USERPLAYER ? AIPLAYER : USERPLAYER));
                node->clear_square(pos);
                alpha = std::max(alpha, value);
                if (alpha >= beta)
                    break;
            }
        }
        return value;
}

tic_tac_toe::game::game() {
    reset();
}

void tic_tac_toe::game::reset() {
    m_player_move = false;
    m_board.reset();
}

bool tic_tac_toe::game::is_player_move() {
    return m_player_move;
}
bool tic_tac_toe::game::is_over() {
    return m_board.evaluate() != INDETERMINATE;
}

bool tic_tac_toe::game::make_move(size_t row, size_t col) {
    int_fast32_t pos = 1 << row * 3 + col;
    if (!is_player_move() || is_over() || m_board.is_occupied(pos))
        return false;
    m_board.set(pos, USERPLAYER);
    m_player_move = false;
    return true;
}
bool tic_tac_toe::game::computer_move() {
    if (is_player_move() || is_over())
        return false;
    int_fast32_t pos = 1, best_pos = -1;
    int8_t best_score = -2;
    for (size_t i = 0; i < 9; i++, pos <<= 1) {
        if (!m_board.is_occupied(pos)) {
            m_board.set(pos, AIPLAYER);
            int8_t score = -negamax(&m_board, 8, -3, 3, -1, USERPLAYER);
            m_board.clear_square(pos);

            if (score > best_score) {
                best_score = score;
                best_pos = pos;
            }
        }
    }
    m_board.set(best_pos, AIPLAYER);
    m_player_move = true;
    return true;
}

void tic_tac_toe::game::display() {
    m_board.display();
}
