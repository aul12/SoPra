/**
 * @file ExitScreen.hpp
 * @author paul
 * @date 26.12.18
 * @brief Declaration of the ExitScreen class
 */

#ifndef EXITSCREEN_HPP
#define EXITSCREEN_HPP

#include "Screen.hpp"

namespace view {
    /**
     * This class doesn't implement a real screen, it only closes the current window.
     * @see Screen
     */
    class ExitScreen : public Screen {
    public:
        ExitScreen(sf::RenderWindow &renderWindow);

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) -> std::shared_ptr<Screen> override;
    };
}

#endif
