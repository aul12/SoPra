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
    /**
     * This screen displays the help message from the Res/Help.txt file.
     * @see Screen
     */
    class HelpScreen : public Screen {
    public:
        HelpScreen(sf::RenderWindow &renderWindow);

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) ->  std::shared_ptr<Screen> override;
    private:
        Button backButton;
        sf::Font font;
        sf::Text helpText;
    };
}


#endif //TEST_HELPSCREEN_HPP
