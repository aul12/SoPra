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

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) ->  std::shared_ptr<Screen>;
    private:
        sf::Texture obstacleBottomTexture, obstacleTopTexture, playerTexture,
            doublePointsTexture,invulnerableTexture,trollTexture, turboModeTexture;
        sf::Text pointText;
        sf::Font font;
    };
}

#endif //TEST_GAMESCREEN_HPP
