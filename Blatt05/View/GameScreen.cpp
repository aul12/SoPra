/**
 * @file GameScreen.cpp
 * @author paul
 * @date 23.12.18
 * @brief GameScreen @TODO
 */

#include <iostream>
#include <sstream>
#include "GameScreen.hpp"
#include "../Controller/Config.hpp"
#include "../Model/Item.hpp"
#include "../Model/DoublePoints.hpp"
#include "../Model/Invulnerable.hpp"
#include "../Model/TurboMode.hpp"
#include "../Model/Troll.hpp"

namespace view {
    GameScreen::GameScreen(sf::RenderWindow &renderWindow) : Screen{renderWindow} {
        if (!obstacleBottomTexture.loadFromFile("../Res/turm_ravenclaw.png") ||
            !obstacleTopTexture.loadFromFile("../Res/dementor.png") ||
            !playerTexture.loadFromFile("../Res/harry.png") ||
            !invulnerableTexture.loadFromFile("../Res/item_gruen.png") ||
            !doublePointsTexture.loadFromFile("../Res/item_blau.png") ||
            !trollTexture.loadFromFile("../Res/item_rot.png") ||
            !turboModeTexture.loadFromFile("../Res/item_silber.png")) {
            throw std::runtime_error("Could not open texture files");
        }

        if(!font.loadFromFile("../Res/Roboto-Regular.ttf")) {
            throw std::runtime_error("Could not load font");
        }

        pointText.setPosition(10,10);
        pointText.setCharacterSize(20);
        pointText.setFont(font);
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4 // Travis uses some ancient version of sfml
        pointText.setFillColor(sf::Color::Black);
#else
        pointText.setColor(sf::Color::Black);
#endif
    }

    auto GameScreen::run() -> ScreenResult {
        sf::Clock pressClock, frameClock;
        bool isPressed = false;
        controller::Environment environment{"../config.json"};
        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        return ScreenResult::EXIT;
                    case sf::Event::KeyPressed:
                        if(isPressed) {
                            environment.playerUp(pressClock.getElapsedTime().asSeconds());
                        }
                        isPressed = true;
                        pressClock.restart();
                        break;
                    case sf::Event::KeyReleased:
                        environment.playerUp(pressClock.getElapsedTime().asSeconds());
                        isPressed = false;
                        break;
                    default:
                        break;
                }
            }

            double time = frameClock.getElapsedTime().asSeconds();
            frameClock.restart();
            //std::cout << "FPS: " << (1/time) << std::endl;

            if(environment.update(time) == controller::UpdateResult::GAME_OVER) {
                return view::ScreenResult::GAME_OVER;
            }

            renderWindow.clear(sf::Color::White);

            float pixelPerMeter = static_cast<float>(
                    renderWindow.getSize().y / environment.getConfig().environment.height);

            for (const auto obstacle : environment.getObstacles()) {
                sf::RectangleShape obstacleDraw;
                model::Vec obstaclePos = environment.toLocal(obstacle->getBoundingRect().topLeft()) * pixelPerMeter;

                obstacleDraw.setPosition(
                        static_cast<float>(obstaclePos.get(0)),
                        static_cast<float>(obstaclePos.get(1)));
                obstacleDraw.setSize({
                                             static_cast<float>(obstacle->getSize().get(0) * pixelPerMeter),
                                             static_cast<float>(obstacle->getSize().get(1) * pixelPerMeter)
                                     });
                if (obstacle->getObstacleSide() == model::ObstacleSide::TOP) {
                    obstacleDraw.setTexture(&obstacleTopTexture);
                } else {
                    obstacleDraw.setTexture(&obstacleBottomTexture);
                }
                obstacleDraw.setOutlineThickness(3);
                obstacleDraw.setOutlineColor(sf::Color::Red);

                renderWindow.draw(obstacleDraw);
            }

            for (const auto item: environment.getItems()) {
                sf::RectangleShape itemDraw;

                std::shared_ptr<model::GameItem> gItem = item;

                model::Vec obstaclePos = environment.toLocal(gItem->getBoundingRect().topLeft()) * pixelPerMeter;

                itemDraw.setPosition(
                        static_cast<float>(obstaclePos.get(0)),
                        static_cast<float>(obstaclePos.get(1)));
                itemDraw.setSize({
                                             static_cast<float>(gItem->getSize().get(0) * pixelPerMeter),
                                             static_cast<float>(gItem->getSize().get(1) * pixelPerMeter)
                                     });

                if (std::dynamic_pointer_cast<model::TurboMode>(item).get() != nullptr) {
                    itemDraw.setTexture(&turboModeTexture);
                } else if (std::dynamic_pointer_cast<model::Troll>(item).get() != nullptr) {
                    itemDraw.setTexture(&trollTexture);
                } else if (std::dynamic_pointer_cast<model::DoublePoints>(item).get() != nullptr) {
                    itemDraw.setTexture(&doublePointsTexture);
                } else if (std::dynamic_pointer_cast<model::Invulnerable>(item).get() != nullptr) {
                    itemDraw.setTexture(&invulnerableTexture);
                } else {
                    throw std::runtime_error("Wrong typeid");
                }

                renderWindow.draw(itemDraw);
            }

            sf::RectangleShape playerDraw;
            model::Vec playerPos =
                    environment.toLocal(environment.getPlayer().getBoundingRect().topLeft()) * pixelPerMeter;
            playerDraw.setPosition(
                    static_cast<float>(playerPos.get(0)),
                    static_cast<float>(playerPos.get(1)));
            playerDraw.setSize({
                                       static_cast<float>(environment.getPlayer().getSize().get(0) * pixelPerMeter),
                                       static_cast<float>(environment.getPlayer().getSize().get(1) * pixelPerMeter)
                               });
            playerDraw.setTexture(&playerTexture);
            renderWindow.draw(playerDraw);

            std::stringstream pointsStream;
            pointsStream << "Points: " << environment.getPoints();
            pointText.setString(pointsStream.str());
            renderWindow.draw(pointText);

            renderWindow.display();
        }
        return ScreenResult::EXIT;
    }
}