/**
 * @file HighscoreScreen.hpp
 * @author paul
 * @date 24.12.18
 * @brief Declaration of the HighscoreScreen
 */

#ifndef HIGHSCORESCREEN_HPP
#define HIGHSCORESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "../Controller/ResourceConfig.hpp"

namespace view {
    /**
     * This screen display the highscore.
     * @see Screen
     */
    class HighscoreScreen : public Screen {
    public:
        HighscoreScreen(sf::RenderWindow &renderWindow, const controller::ResourceConfig &resourceConfig);

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) ->  std::shared_ptr<Screen> override;

    private:
        sf::Font font;
        Button backButton;
        sf::Text nameText,scoreText;
    };
}

#endif
