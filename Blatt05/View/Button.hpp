/**
 * @file Button.hpp
 * @author paul
 * @date 23.12.18
 * @brief Button @TODO
 */

#ifndef TEST_BUTTON_HPP
#define TEST_BUTTON_HPP


#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
    Button() = default;
    Button(std::string text, sf::Font &font, float posX, float posY, float sizeX, float sizeY, int fontSize = 30,
            sf::Color background = sf::Color::Black, sf::Color textColor = sf::Color::White);
    auto contains(float x, float y) -> bool;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Text text;
    sf::RectangleShape rectangleShape;
};


#endif //TEST_BUTTON_HPP
