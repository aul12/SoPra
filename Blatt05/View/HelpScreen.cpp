/**
 * @file HelpScreen.cpp
 * @author paul
 * @date 23.12.18
 * @brief HelpScreen implementation
 */

#include "HelpScreen.hpp"

namespace view {
    HelpScreen::HelpScreen(sf::RenderWindow &renderWindow) : Screen(renderWindow) {
        if(!font.loadFromFile("../Res/Roboto-Regular.ttf")) {
            throw std::runtime_error("Could not load font");
        }

        auto size = renderWindow.getSize();
        backButton = Button{"Back", font, size.x*0.1f, size.y - 70.0f, size.x*0.8f, 50};
    }

    auto HelpScreen::run() -> ScreenResult {
        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        return ScreenResult::EXIT;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (backButton.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return ScreenResult::START;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            renderWindow.clear(sf::Color::White);
            backButton.render(renderWindow);

            renderWindow.display();
        }
        return ScreenResult::EXIT;
    }

}
