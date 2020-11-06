#if !defined(TIC_TAC_TOE_GAME_BOARD_HPP)
#define TIC_TAC_TOE_GAME_BOARD_HPP

#define SQUARE0 0b000000001
#define SQUARE1 0b000000010
#define SQUARE2 0b000000100
#define SQUARE3 0b000001000
#define SQUARE4 0b000010000
#define SQUARE5 0b000100000
#define SQUARE6 0b001000000
#define SQUARE7 0b010000000
#define SQUARE8 0b100000000

#define FULLBOARD 0b111111111

#define USERPLAYER 0
#define AIPLAYER 9

#define USERPLAYERWIN -1
#define DRAW 0
#define AIPLAYERWIN 1
#define INDETERMINATE 2

#include <stdint.h>
#include <cstddef>

namespace tic_tac_toe {

class board {
private:
    int_fast32_t m_state;

public:
    board();

    void reset();

    bool is_occupied(const int_fast32_t square);
    void clear_square(const int_fast32_t square);
    void set(const int_fast32_t square, const size_t player);

    int8_t evaluate();

    void display();
};

} // namespace tic_tac_toe


#endif // TIC_TAC_TOE_GAME_BOARD_HPP
