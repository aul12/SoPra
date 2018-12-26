/**
 * @file StartScreen.cpp
 * @author paul
 * @date 23.12.18
 * @brief Implementation of the StartScreen class
 */

#include <iostream>
#include "StartScreen.hpp"
#include "Button.hpp"

namespace view {
    StartScreen::StartScreen(sf::RenderWindow &renderWindow) : Screen(renderWindow) {
        if(!font.loadFromFile("../Res/harry_p.ttf")) {
            throw std::runtime_error("Could not load font!");
        }

        auto size = renderWindow.getSize();
        game = Button{"Start game", font, size.x*0.1f, 20, size.x*0.8f, 50};
        highscore = Button{"Highscore", font, size.x*0.1f, 90, size.x*0.8f, 50};
        help = Button{"Help", font, size.x*0.1f, 160, size.x*0.8f, 50};
        exit = Button{"Exit", font, size.x*0.1f, size.y-70.0f, size.x*0.8f, 50};
    }

    auto StartScreen::run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) -> std::shared_ptr<Screen> {
        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        return screens.at(ScreenResult::EXIT);
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if(game.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return screens.at(ScreenResult::GAME);
                            } else if (highscore.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return screens.at(ScreenResult::HIGHSCORE);
                            } else if (help.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return screens.at(ScreenResult::HELP);
                            } else if (exit.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return screens.at(ScreenResult::EXIT);
                            }
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(event.key.code == sf::Keyboard::Escape) {
                            return screens.at(ScreenResult::EXIT);
                        }
                    default:
                        break;
                }
            }

            renderWindow.clear(sf::Color{0xEC, 0xB9, 0x39, 255}); // Color stolen from: http://harrypotter.wikia.com/wiki/Hufflepuff

            game.render(renderWindow);
            help.render(renderWindow);
            highscore.render(renderWindow);
            exit.render(renderWindow);

            renderWindow.display();
        }
        return screens.at(ScreenResult::EXIT);
    }
}
