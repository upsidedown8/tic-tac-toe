#include "gui.hpp"

tic_tac_toe::gui::gui() {
    m_cross.loadFromFile("assets/cross.png");
    m_naught.loadFromFile("assets/naught.png");
    m_board.loadFromFile("assets/board.png");
    m_line.loadFromFile("assets/line.png");

    m_cross_sprite.setTexture(m_cross);
    m_naught_sprite.setTexture(m_naught);
    m_board_sprite.setTexture(m_board);
    m_line_sprite.setTexture(m_line);
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
            bool draw_sprite = true;
            int angle = 0, row = 0, col = 0;
            switch(m_game.m_board.get_end_code()) {
                case 0: // first row
                    angle = 90;
                    break;
                case 1: // second row
                    angle = 90;
                    row = 1;
                    break;
                case 2: // third row
                    angle = 90;
                    row = 2;
                    break;
                case 3: // first col
                    break;
                case 4: // second col
                    col = 1;
                    break;
                case 5: // third col
                    col = 2;
                    break;
                case 6: // \ diagonal
                    angle = -45;
                    break;
                case 7: // / diagonal
                    angle = 45;
                    row = 2;
                    col = 2;
                    break;
                default: // draw
                    draw_sprite = false;
                    break;
            }
            if (draw_sprite) {
                // float width = window.getSize().x;
                // float height = window.getSize().y;
                // fix rotation and position
                // window.draw(m_line_sprite);
            }
        }

        window.display();
    }
}

