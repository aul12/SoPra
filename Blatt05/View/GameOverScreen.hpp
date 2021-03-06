/**
 * @file GameOverScreen.hpp
 * @author paul
 * @date 24.12.18
 * @brief Declaration of the GameOverScreen
 */

#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

#include "../Controller/ResourceConfig.hpp"

namespace view {
    /**
     * This screen displays an Game Over Dialog with the option to save the current score.
     * @see Screen
     */
    class GameOverScreen : public Screen {
    public:
        GameOverScreen(sf::RenderWindow &renderWindow, const controller::ResourceConfig &resourceConfig);

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) ->  std::shared_ptr<Screen> override;

        /**
         * This function is used to store the points for saving them to the highscore
         * @param points the number of points
         */
        void submitPoints(int points);
    private:
        sf::Font font;
        Button homeButton, playAgainButton;
        sf::Text pointsText, enterNameText, nameText;
        int points;
    };
}

#endif
