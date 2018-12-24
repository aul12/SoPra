/**
 * @file GameOverScreen.hpp
 * @author paul
 * @date 24.12.18
 * @brief GameOverScreen @TODO
 */

#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

namespace view {
    class GameOverScreen : public Screen {
    public:
        GameOverScreen(sf::RenderWindow &renderWindow);

        virtual ScreenResult run();

    private:
        sf::Font font;
        Button homeButton, playAgainButton;
    };
}

#endif
