/**
 * @file HelpScreen.cpp
 * @author paul
 * @date 23.12.18
 * @brief HelpScreen implementation
 */

#include "HelpScreen.hpp"

namespace view {
    view::HelpScreen::HelpScreen(sf::RenderWindow &renderWindow) : Screen(renderWindow) {
        if(!font.loadFromFile("../Res/Roboto-Regular.ttf")) {
            throw std::runtime_error("Could not load font");
        }

        auto size = renderWindow.getSize();
        exit = Button{"Exit", font, size.x*0.1f, 20, size.x*0.8f, 50};
    }

    view::ScreenResult view::HelpScreen::run() {
        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        return ScreenResult::EXIT;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if(exit.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return ScreenResult::START;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            renderWindow.clear(sf::Color{255,255,255,255});

            exit.render(renderWindow);

            renderWindow.display();
        }
        return ScreenResult::EXIT;
    }

}
