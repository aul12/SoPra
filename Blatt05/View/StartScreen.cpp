/**
 * @file StartScreen.cpp
 * @author paul
 * @date 23.12.18
 * @brief StartScreen @TODO
 */

#include <iostream>
#include "StartScreen.hpp"
#include "Button.hpp"

namespace view {
    StartScreen::StartScreen(sf::RenderWindow &renderWindow) : Screen(renderWindow) {
        //@TODO how about not hardcoding the font?
        if(!font.loadFromFile("/usr/share/fonts/truetype/roboto/hinted/Roboto-Regular.ttf")) {
            throw std::runtime_error("Could not load font!");
        }
    }

    auto StartScreen::run() -> ScreenResult {
        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    return ScreenResult::EXIT;
                }
            }

            renderWindow.clear(sf::Color{255,255,255,255});
            auto size = renderWindow.getSize();

            Button button{"Test", font, size.x*0.1f, 20, size.x*0.8f, 50};
            button.render(renderWindow);
            Button button2{"Test2", font, size.x*0.1f, 90, size.x*0.8f, 50};
            button2.render(renderWindow);

            renderWindow.display();
        }
        return ScreenResult::EXIT;
    }
}
