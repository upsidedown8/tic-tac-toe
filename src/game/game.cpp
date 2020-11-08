#include "game.hpp"

#include <algorithm>
#include <vector>

int tic_tac_toe::game::negamax(board *node, int player) {
    int value = node->evaluate();
    if (value != INDETERMINATE)
        return value * (player == AIPLAYER ? 1 : -1);

    int score = -2;
    int_fast32_t pos = 1;

    for (size_t i = 0; i < 9; i++, pos <<= 1) {
        if (!node->is_occupied(pos)) {
            node->set(pos, player);
            int move_score = -negamax(node, player == AIPLAYER ? USERPLAYER : AIPLAYER);
            node->clear_square(pos);
            score = std::max(score, move_score);
        }
    }

    return score;
}
int_fast32_t tic_tac_toe::game::best_move(board *node, int player) {
    int score = -2;
    int_fast32_t move = -1, pos = 1;

    for (size_t i = 0; i < 9; i++, pos <<= 1) {
        if (!node->is_occupied(pos)) {
            node->set(pos, player);
            int move_score = -negamax(node, player == AIPLAYER ? USERPLAYER : AIPLAYER);
            node->clear_square(pos);
            if (move_score >= score) {
                score = move_score;
                move = pos;
            }
        }
    }

    return move;
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
    // std::vector<int_fast32_t> moves;
    // int_fast32_t pos = 1;
    // int best_score = -2;

    // if (!moves.size())
    //     return false;
    // m_board.set(moves[rand() % moves.size()], AIPLAYER);

    m_board.set(best_move(&m_board, AIPLAYER), AIPLAYER);

    m_player_move = true;
    m_move++;
    return true;
}
