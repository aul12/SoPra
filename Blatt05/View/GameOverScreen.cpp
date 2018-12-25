/**
 * @file GameOverScreen.cpp
 * @author paul
 * @date 24.12.18
 * @brief GameOverScreen @TODO
 */

#include "GameOverScreen.hpp"

namespace view {
    GameOverScreen::GameOverScreen(sf::RenderWindow &renderWindow) : Screen(renderWindow) {
        if(!font.loadFromFile("../Res/harry_p.ttf")) {
            throw std::runtime_error("Could not load font");
        }
        auto size = renderWindow.getSize();
        playAgainButton = Button{"Play again", font, size.x*0.1f, 20, size.x*0.8f, 50};
        homeButton = Button{"Back to the start page", font, size.x*0.1f, 90, size.x*0.8f, 50};
    }

    auto view::GameOverScreen::run() -> ScreenResult{
        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        return ScreenResult::EXIT;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (homeButton.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return ScreenResult::START;
                            } else if (playAgainButton.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return ScreenResult::GAME;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            renderWindow.clear(sf::Color::White);

            homeButton.render(renderWindow);
            playAgainButton.render(renderWindow);

            renderWindow.display();
        }
        return ScreenResult::EXIT;
    }
}