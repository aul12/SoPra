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

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) ->  std::shared_ptr<Screen> override;

    private:
        sf::Font font;
        Button backButton;
        sf::Text nameText,scoreText;
    };
}

#endif
