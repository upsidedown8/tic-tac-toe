#include "board.hpp"
#include <iostream>

const int_fast32_t wins[] {
    0b000000111, // first row
    0b000111000, // second row
    0b111000000, // third row
    0b001001001, // first col
    0b010010010, // second col
    0b100100100, // third col
    0b100010001, // \ diagonal
    0b001010100  // / diagonal
};

tic_tac_toe::board::board(int_fast32_t state) {
    m_state = state & 0b111111111111111111;
}

tic_tac_toe::board::board() {
    reset();
}

tic_tac_toe::board *tic_tac_toe::board::copy() {
    return new board(m_state);
}

void tic_tac_toe::board::reset() {
    m_state = 0;
}

bool tic_tac_toe::board::is_occupied(const int_fast32_t square) {
    return !!(
        (m_state & square) |
        (m_state & (square << AIPLAYER))
    );
}
bool tic_tac_toe::board::is_naught(const int_fast32_t square) {
    return
        is_occupied(square) &&
        (m_state & (square << AIPLAYER));
}
bool tic_tac_toe::board::is_cross(const int_fast32_t square) {
    return is_occupied(square) && !is_naught(square);
}

void tic_tac_toe::board::clear_square(const int_fast32_t square) {
    m_state &= ~(
        square |
        square << AIPLAYER
    );
}
void tic_tac_toe::board::set(const int_fast32_t square, const size_t player) {
    m_state |= square << player;
}

int8_t tic_tac_toe::board::evaluate() {
    // player 1
    for (int_fast32_t win : wins)
        if ((m_state & win) == win)
            return USERPLAYERWIN;
    
    // player 2
    for (int_fast32_t win : wins)
        if (((m_state>>AIPLAYER) & win) == win)
            return AIPLAYERWIN;

    // check for draw
    if(((m_state | (m_state>>AIPLAYER)) & FULLBOARD) == FULLBOARD)
        return DRAW;
            
    return INDETERMINATE;
}
int8_t tic_tac_toe::board::get_end_code() {
    int i = 0;
    // player 1
    for (int_fast32_t win : wins) {
        if ((m_state & win)             == win ||
            ((m_state>>AIPLAYER) & win) == win) {
            return i;
        }
        i++;
    }

    // no need to draw a line
    return -1;
}

void tic_tac_toe::board::display() {
    const char *players = " xo";
    
    for (size_t row = 0; row < 3; row++) {
        for (size_t col = 0; col < 3; col++) {
            size_t pos = 1 << (row * 3 + col);
            std::cout << ' ' << players[
                !!is_occupied(pos) +
                !!(m_state & (pos << AIPLAYER))
            ] << ' ';
            if (col + 1 < 3)
                std::cout << '|';
        }
        std::cout << std::endl;
        if (row + 1 < 3)
            std::cout << "-----------" << std::endl;
    }
}
