/**
 * @file HighscoreScreen.cpp
 * @author paul
 * @date 24.12.18
 * @brief Implementation of the HighscoreScreen
 */

#include "HighscoreScreen.hpp"
#include <sstream>
#include <iomanip>
#include "../Model/HighscoreSaver.hpp"

namespace view {
    HighscoreScreen::HighscoreScreen(sf::RenderWindow &renderWindow, const controller::ResourceConfig &resourceConfig)
            : Screen(renderWindow) {
        if (!font.loadFromFile(resourceConfig.font)) {
            throw std::runtime_error("Could not load font!");
        }

        auto size = renderWindow.getSize();
        backButton = Button{"Back", font, size.x*0.1f, size.y - 70.0f, size.x*0.8f, 50};

        nameText.setFont(font);
        nameText.setCharacterSize(40);
        nameText.setPosition(size.x*0.1f,30);
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4 // Travis uses some ancient version of sfml
        nameText.setFillColor(sf::Color::Black);
#else
        nameText.setColor(sf::Color::Black);
#endif
        scoreText.setFont(font);
        scoreText.setCharacterSize(40);
        scoreText.setPosition(size.x*0.5f,30);
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4 // Travis uses some ancient version of sfml
        scoreText.setFillColor(sf::Color::Black);
#else
        scoreText.setColor(sf::Color::Black);
#endif
    }

    auto HighscoreScreen::run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) -> std::shared_ptr<Screen> {
        model::HighscoreSaver highscoreSaver{"highscore.json"};

        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        return screens.at(ScreenResult::EXIT);
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (backButton.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return screens.at(ScreenResult::START);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            renderWindow.clear(sf::Color{0xEC, 0xB9, 0x39, 255}); // Color stolen from: http://harrypotter.wikia.com/wiki/Hufflepuff

            std::stringstream nameStream, scoreStream;
            const auto highscores = highscoreSaver.retrieveHighscore(5);
            for(const auto &highscore : highscores) {
                const auto [name, score] = highscore;
                nameStream << name << std::endl;
                scoreStream  << score << std::endl;
            }

            nameText.setString(nameStream.str());
            scoreText.setString(scoreStream.str());

            renderWindow.draw(nameText);
            renderWindow.draw(scoreText);
            renderWindow.draw(backButton);

            renderWindow.display();
        }
        return screens.at(ScreenResult::EXIT);
    }
}
