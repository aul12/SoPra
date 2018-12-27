/**
 * @file ExitScreen.cpp
 * @author paul
 * @date 26.12.18
 * @brief Declaration of the ExitScreen class
 */

#include "ExitScreen.hpp"

namespace view {
    ExitScreen::ExitScreen(sf::RenderWindow &renderWindow)
        : Screen(renderWindow) {}

    auto ExitScreen::run(std::map<ScreenResult, std::shared_ptr<view::Screen>> &screens) -> std::shared_ptr<Screen> {
        renderWindow.close();

        return screens.at(ScreenResult::EXIT);
    }
}
