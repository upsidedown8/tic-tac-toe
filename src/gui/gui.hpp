#if !defined(TIC_TAC_TOE_GUI_GUI_HPP)
#define TIC_TAC_TOE_GUI_GUI_HPP

#include <SFML/Graphics.hpp>
#include "game/game.hpp"

namespace tic_tac_toe {
    
class gui {
private:
    game m_game;
    sf::Texture m_cross, m_naught, m_board;
    sf::Sprite m_cross_sprite, m_naught_sprite, m_board_sprite;
    sf::RenderWindow m_window;

public:
    gui();

    void start();
};

} // namespace tic_tac_toe


#endif // TIC_TAC_TOE_GUI_GUI_HPP
