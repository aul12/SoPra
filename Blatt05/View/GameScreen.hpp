/**
 * @file GameScreen.hpp
 * @author paul
 * @date 23.12.18
 * @brief GameScreen @TODO
 */

#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP


#include <SFML/Graphics/Texture.hpp>
#include "../Controller/Environment.hpp"
#include "Screen.hpp"

namespace view {
    class GameScreen : public Screen {
    public:
        GameScreen(sf::RenderWindow &renderWindow);

        ScreenResult run();
    private:
        sf::Texture obstacleBottomTexture, obstacleTopTexture, playerTexture,
            doublePointsTexture,invulnerableTexture,trollTexture, turboModeTexture;
        controller::Environment environment;
    };
}

#endif //TEST_GAMESCREEN_HPP
