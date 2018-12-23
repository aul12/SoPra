/**
 * @file StartScreen.hpp
 * @author paul
 * @date 23.12.18
 * @brief Declaration of the StartScreen class
 */

#ifndef STARTSCREEN_HPP
#define STARTSCREEN_HPP

#include "Screen.hpp"

namespace view {
    class StartScreen : public Screen {
    public:
        StartScreen(sf::RenderWindow &renderWindow);
        auto run() -> ScreenResult;

    private:
        sf::Font font;
    };
}

#endif
