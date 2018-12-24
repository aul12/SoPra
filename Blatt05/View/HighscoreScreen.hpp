/**
 * @file HighscoreScreen.hpp
 * @author paul
 * @date 24.12.18
 * @brief HighscoreScreen @TODO
 */

#ifndef HIGHSCORESCREEN_HPP
#define HIGHSCORESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

namespace view {
    class HighscoreScreen : public Screen {
    public:
        HighscoreScreen(sf::RenderWindow &renderWindow);

        auto run() -> ScreenResult;

    private:
        sf::Font font;
        Button backButton;
    };
}

#endif
