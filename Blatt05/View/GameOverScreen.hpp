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
    /**
     * This screen displays an Game Over Dialog with the option to save the current score.
     * @see Screen
     */
    class GameOverScreen : public Screen {
    public:
        GameOverScreen(sf::RenderWindow &renderWindow);

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
