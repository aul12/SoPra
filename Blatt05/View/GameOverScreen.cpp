/**
 * @file GameOverScreen.cpp
 * @author paul
 * @date 24.12.18
 * @brief GameOverScreen @TODO
 */

#include "GameOverScreen.hpp"
#include "../Model/HighscoreSaver.hpp"

#include <sstream>

namespace view {
    GameOverScreen::GameOverScreen(sf::RenderWindow &renderWindow) : Screen(renderWindow) {
        if(!font.loadFromFile("../Res/harry_p.ttf")) {
            throw std::runtime_error("Could not load font");
        }
        auto size = renderWindow.getSize();
        playAgainButton = Button{"Play again", font, size.x*0.1f, size.y - 140.0f, size.x*0.8f, 50};
        homeButton = Button{"Back to the start page", font, size.x*0.1f, size.y - 70.0f, size.x*0.8f, 50};

        pointsText.setPosition(size.x*0.1f,30);
        pointsText.setFont(font);
        pointsText.setCharacterSize(50);
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4 // Travis uses some ancient version of sfml
        pointsText.setFillColor(sf::Color::Black);
#else
        pointsText.setColor(sf::Color::Black);
#endif

        enterNameText.setPosition(size.x*0.1f,150);
        enterNameText.setFont(font);
        enterNameText.setCharacterSize(30);
        enterNameText.setString("Enter your name:");
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4 // Travis uses some ancient version of sfml
        enterNameText.setFillColor(sf::Color::Black);
#else
        enterNameText.setColor(sf::Color::Black);
#endif

        nameText.setPosition(size.x*0.5f,150);
        nameText.setFont(font);
        nameText.setCharacterSize(30);
        nameText.setString("");
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4 // Travis uses some ancient version of sfml
        nameText.setFillColor(sf::Color::Black);
#else
        nameText.setColor(sf::Color::Black);
#endif
    }

    auto GameOverScreen::run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) -> std::shared_ptr<Screen> {
        std::string name;
        model::HighscoreSaver highscoreSaver{"../highscore.json"};
        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        return screens.at(ScreenResult::EXIT);
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (homeButton.contains(event.mouseButton.x, event.mouseButton.y)) {
                                if(!name.empty()) {
                                    highscoreSaver.insert(points, name);
                                }
                                return screens.at(ScreenResult::START);
                            } else if (playAgainButton.contains(event.mouseButton.x, event.mouseButton.y)) {
                                if(!name.empty()) {
                                    highscoreSaver.insert(points, name);
                                }
                                return screens.at(ScreenResult::GAME);
                            }
                        }
                        break;
                    case sf::Event::TextEntered:
                        if(event.text.unicode < 128) {
                            if (event.text.unicode == '\b') { //Backspace
                                if (name.length() > 0) {
                                    name.pop_back();
                                }
                            } else if (name.length() < 32) {
                                name.push_back(static_cast<char>(event.text.unicode));
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            renderWindow.clear(sf::Color{0xEC, 0xB9, 0x39, 255}); // Color stolen from: http://harrypotter.wikia.com/wiki/Hufflepuff

            std::stringstream pointsStream;
            pointsStream << "Points:\t" << this->points;
            pointsText.setString(pointsStream.str());

            nameText.setString(name);

            renderWindow.draw(pointsText);
            renderWindow.draw(enterNameText);
            renderWindow.draw(nameText);
            homeButton.render(renderWindow);
            playAgainButton.render(renderWindow);

            renderWindow.display();
        }
        return screens.at(ScreenResult::EXIT);
    }

    void GameOverScreen::submitPoints(int points) {
        this->points = points;
    }
}