/**
 * @file GameScreen.hpp
 * @author paul
 * @date 23.12.18
 * @brief Declaration of the GameScreen
 */

#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP


#include <SFML/Graphics/Texture.hpp>
#include "Screen.hpp"

#include "../Controller/Environment.hpp"
#include "../Controller/ResourceConfig.hpp"

namespace view {
    /**
     * This screen displays the actual game.
     * @see Screen
     */
    class GameScreen : public Screen {
    public:
        GameScreen(sf::RenderWindow &renderWindow, const controller::ResourceConfig &resourceConfig,
                const controller::GameConfig &gameConfig);

        auto run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) ->  std::shared_ptr<Screen> override;
    private:
        sf::Texture obstacleBottomTexture, obstacleTopTexture, playerTexture,
            doublePointsTexture,invulnerableTexture,trollTexture, turboModeTexture;
        sf::Text statusText;
        sf::Font font;
        controller::GameConfig gameConfig;
    };
}

#endif //TEST_GAMESCREEN_HPP
