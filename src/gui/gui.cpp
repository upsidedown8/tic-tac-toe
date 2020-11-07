#include "gui.hpp"

tic_tac_toe::gui::gui() {
    m_cross.loadFromFile("assets/cross.png");
    m_naught.loadFromFile("assets/naught.png");
    m_board.loadFromFile("assets/board.png");

    m_cross_sprite.setTexture(m_cross);
    m_naught_sprite.setTexture(m_naught);
    m_board_sprite.setTexture(m_board);
}

void tic_tac_toe::gui::start() {
    sf::RenderWindow window(sf::VideoMode(240, 240), "Tic Tac Toe");
    sf::Vector2u size = window.getSize();

    m_board_sprite.setScale(sf::Vector2f(
        size.x / m_board_sprite.getLocalBounds().width,
        size.y / m_board_sprite.getLocalBounds().height
    ));
    m_cross_sprite.setScale(sf::Vector2f(
        size.x / m_cross_sprite.getLocalBounds().width / 3,
        size.y / m_cross_sprite.getLocalBounds().height / 3
    ));
    m_naught_sprite.setScale(sf::Vector2f(
        size.x / m_naught_sprite.getLocalBounds().width / 3,
        size.y / m_naught_sprite.getLocalBounds().height / 3
    ));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                if (pos.x >= 0 && pos.x <= window.getSize().x &&
                    pos.y >= 0 && pos.y <= window.getSize().y) {
                        size_t row = pos.y * 3 / window.getSize().y;
                        size_t col = pos.x * 3 / window.getSize().x;

                        m_game.computer_move();
                        m_game.make_move(row, col);
                        m_game.computer_move();
                }
            }
        }

        window.clear();

        window.draw(m_board_sprite);

        int_fast32_t i = 1;
        for (size_t row = 0; row < 3; row++) {
            for (size_t col = 0; col < 3; col++, i <<= 1) {
                if (m_game.m_board.is_naught(i)) {
                    m_naught_sprite.setPosition(sf::Vector2f(
                        size.x * col / 3,
                        size.y * row / 3
                    ));
                    window.draw(m_naught_sprite);
                } else if (m_game.m_board.is_cross(i)) {
                    m_cross_sprite.setPosition(sf::Vector2f(
                        size.x * col / 3,
                        size.y * row / 3
                    ));
                    window.draw(m_cross_sprite);
                }
            }
        }

        if (m_game.is_over()) {

        }

        window.display();
    }
}

