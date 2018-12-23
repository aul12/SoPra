/**
 * @file Button.hpp
 * @author paul
 * @date 23.12.18
 * @brief Button @TODO
 */

#ifndef TEST_BUTTON_HPP
#define TEST_BUTTON_HPP


#include <SFML/Graphics.hpp>

class Button {
public:
    Button() = default;
    Button(std::string text, sf::Font &font, float posX, float posY, float sizeX, float sizeY, int fontSize = 30,
            sf::Color background = sf::Color{0,0,0,255}, sf::Color textColor = sf::Color{255,255,255,255});
    void render(sf::RenderWindow &window);
    auto contains(float x, float y) -> bool;
private:
    sf::Text text;
    sf::RectangleShape rectangleShape;
};


#endif //TEST_BUTTON_HPP
