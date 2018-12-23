/**
 * @file GameScreen.cpp
 * @author paul
 * @date 23.12.18
 * @brief GameScreen @TODO
 */

#include <iostream>
#include "GameScreen.hpp"
#include "../Controller/Config.hpp"

namespace view {
    GameScreen::GameScreen(sf::RenderWindow &renderWindow) : Screen{renderWindow}, environment{"../config.json"}{
        if (!obstacleBottomTexture.loadFromFile("../Res/turm_ravenclaw.png") ||
            !obstacleTopTexture.loadFromFile("../Res/dementor.png") ||
            !playerTexture.loadFromFile("../Res/harry.png") ||
            !itemTexture.loadFromFile("../Res/item_blau.png")) {
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
                model::Vec relObstaclePos{obstacle.get()->getBoundingRect().topLeft().get(0) -
                    environment.getPlayer().getPosition().get(0) + environment.getConfig().player.xPosInFrame,
                obstacle.get()->getBoundingRect().topLeft().get(1)};

                std::cout << relObstaclePos.get(0) << "," << relObstaclePos.get(1) << std::endl;

                obstacleDraw.setPosition(
                        static_cast<float>(relObstaclePos.get(0) * pixelPerMeter),
                        static_cast<float>(relObstaclePos.get(1) * pixelPerMeter));
                obstacleDraw.setSize({
                        static_cast<float>(obstacle.get()->getSize().get(0) * pixelPerMeter),
                        static_cast<float>(obstacle.get()->getSize().get(1) * pixelPerMeter)
                });
                if (obstacle.get()->getObstacleSide() == model::ObstacleSide::TOP) {
                    obstacleDraw.setTexture(&obstacleTopTexture);
                } else {
                    obstacleDraw.setTexture(&obstacleBottomTexture);
                }

                renderWindow.draw(obstacleDraw);
            }

            sf::RectangleShape playerDraw;
            playerDraw.setPosition(
                    static_cast<float>(environment.getConfig().player.xPosInFrame * pixelPerMeter),
                    static_cast<float>(environment.getPlayer().getBoundingRect().topLeft().get(1) * pixelPerMeter));
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