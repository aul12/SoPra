/**
 * @file Screen.hpp
 * @author paul
 * @date 23.12.18
 * @brief Declaration of the Screen class
 */

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace view {
    enum class ScreenResult {
        START, HELP, GAME_OVER, GAME, HIGHSCORE, EXIT
    };

    /**
     * This class implements an generic screen interface
     */
    class Screen {
    public:
        /**
         * Generate the screen with a reference to the window
         * @param renderWindow the window on which the screen should draw
         */
        Screen(sf::RenderWindow &renderWindow);

        /**
         * Run the screen until another screen should be shown
         */
        virtual auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) ->  std::shared_ptr<Screen> = 0;

    protected:
        sf::RenderWindow &renderWindow;
    };

}

#endif //TEST_SCREEN_HPP
