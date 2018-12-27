/**
 * @file StartScreen.hpp
 * @author paul
 * @date 23.12.18
 * @brief Declaration of the StartScreen class
 */

#ifndef STARTSCREEN_HPP
#define STARTSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "../Controller/ResourceConfig.hpp"

namespace view {
    /**
     * This screen display the buttons to change to different screens.
     * @see Screen
     */
    class StartScreen : public Screen {
    public:
        StartScreen(sf::RenderWindow &renderWindow, const controller::ResourceConfig &resourceConfig);

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) ->  std::shared_ptr<Screen> override;

    private:
        sf::Font font;
        Button game, help, highscore, exit;
    };
}

#endif
