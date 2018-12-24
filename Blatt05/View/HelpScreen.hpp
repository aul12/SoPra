/**
 * @file HelpScreen.hpp
 * @author paul
 * @date 23.12.18
 * @brief Declaration of the HelpScreen class
 */

#ifndef HELPSCREEN_HPP
#define HELPSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

namespace view {
    class HelpScreen : public Screen {
    public:
        HelpScreen(sf::RenderWindow &renderWindow);
        auto run() -> ScreenResult ;
    private:
        Button backButton;
        sf::Font font;
    };
}


#endif //TEST_HELPSCREEN_HPP
