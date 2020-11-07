#include "game.hpp"

#include <algorithm>
#include <vector>

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
    m_player_move = true;
    m_move = 0;
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
    if (!is_player_move() || is_over() ||
        m_board.is_occupied(pos) ||
        row < 0 || row > 2 ||
        col < 0 || col > 2)
        return false;
    m_board.set(pos, USERPLAYER);
    m_player_move = false;
    m_move++;
    return true;
}
bool tic_tac_toe::game::computer_move() {
    if (is_player_move() || is_over())
        return false;
    std::vector<int_fast32_t> moves;
    int_fast32_t pos = 1;
    int8_t best_score = -2;
    for (size_t i = 0; i < 9; i++, pos <<= 1) {
        if (!m_board.is_occupied(pos)) {
            m_board.set(pos, AIPLAYER);
            int8_t score = -negamax(&m_board, 9 - m_move, -3, 3, -1, USERPLAYER);
            m_board.clear_square(pos);

            if (score >= best_score) {
                if (best_score > score)
                    moves.clear();
                moves.push_back(pos);
                best_score = score;
            }
        }
    }
    if (!moves.size())
        return false;
    m_board.set(moves[rand() % moves.size()], AIPLAYER);
    m_player_move = true;
    m_move++;
    return true;
}
