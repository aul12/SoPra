/**
 * @file ExitScreen.hpp
 * @author paul
 * @date 26.12.18
 * @brief ExitScreen @TODO
 */

#ifndef EXITSCREEN_HPP
#define EXITSCREEN_HPP

#include "Screen.hpp"

namespace view {
    class ExitScreen : public Screen {
    public:
        ExitScreen(sf::RenderWindow &renderWindow);

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) -> std::shared_ptr<Screen> override;
    };
}

#endif
