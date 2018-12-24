/**
 * @file GameScreen.cpp
 * @author paul
 * @date 23.12.18
 * @brief GameScreen @TODO
 */

#include <iostream>
#include "GameScreen.hpp"
#include "../Controller/Config.hpp"
#include "../Model/Item.hpp"
#include "../Model/DoublePoints.hpp"
#include "../Model/Invulnerable.hpp"
#include "../Model/TurboMode.hpp"
#include "../Model/Troll.hpp"

namespace view {
    GameScreen::GameScreen(sf::RenderWindow &renderWindow) : Screen{renderWindow}, environment{"../config.json"}{
        if (!obstacleBottomTexture.loadFromFile("../Res/turm_ravenclaw.png") ||
            !obstacleTopTexture.loadFromFile("../Res/dementor.png") ||
            !playerTexture.loadFromFile("../Res/harry.png") ||
            !invulnerableTexture.loadFromFile("../Res/item_gruen.png") ||
            !doublePointsTexture.loadFromFile("../Res/item_blau.png") ||
            !trollTexture.loadFromFile("../Res/item_rot.png") ||
            !turboModeTexture.loadFromFile("../Res/item_silber.png")) {
            throw std::runtime_error("Could not open texture files");
        }
    }

    ScreenResult GameScreen::run() {
        sf::Clock pressClock, frameClock;
        bool isPressed = false;
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

            if(environment.update(frameClock.getElapsedTime().asSeconds()) == controller::UpdateResult::GAME_OVER) {
                return view::ScreenResult::GAME_OVER;
            }

            frameClock.restart();

            renderWindow.clear(sf::Color{255,255,255,255});

            float pixelPerMeter = static_cast<float>(
                    renderWindow.getSize().y / environment.getConfig().environment.height);

            for (const auto &obstacle : environment.getObstacles()) {
                sf::RectangleShape obstacleDraw;
                model::Vec obstaclePos = environment.toLocal(obstacle.get()->getBoundingRect().topLeft()) * pixelPerMeter;

                obstacleDraw.setPosition(
                        static_cast<float>(obstaclePos.get(0)),
                        static_cast<float>(obstaclePos.get(1)));
                obstacleDraw.setSize({
                                             static_cast<float>(obstacle.get()->getSize().get(0) * pixelPerMeter),
                                             static_cast<float>(obstacle.get()->getSize().get(1) * pixelPerMeter)
                                     });
                if (obstacle.get()->getObstacleSide() == model::ObstacleSide::TOP) {
                    obstacleDraw.setTexture(&obstacleTopTexture);
                } else {
                    obstacleDraw.setTexture(&obstacleBottomTexture);
                }
                obstacleDraw.setOutlineThickness(3);
                obstacleDraw.setOutlineColor(sf::Color{255,0,0,127});

                renderWindow.draw(obstacleDraw);
            }

            for (std::shared_ptr<model::Item> item: environment.getItems()) {
                sf::RectangleShape itemDraw;

                std::shared_ptr<model::GameItem> gItem = item;

                model::Vec obstaclePos = environment.toLocal(gItem.get()->getBoundingRect().topLeft()) * pixelPerMeter;

                itemDraw.setPosition(
                        static_cast<float>(obstaclePos.get(0)),
                        static_cast<float>(obstaclePos.get(1)));
                itemDraw.setSize({
                                             static_cast<float>(gItem.get()->getSize().get(0) * pixelPerMeter),
                                             static_cast<float>(gItem.get()->getSize().get(1) * pixelPerMeter)
                                     });

                //@TODO different textures
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


            renderWindow.display();
        }
        return ScreenResult::EXIT;
    }
}