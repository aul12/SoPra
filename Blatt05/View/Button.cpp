/**
 * @file Button.cpp
 * @author paul
 * @date 23.12.18
 * @brief Button @TODO
 */

#include "Button.hpp"

#include <SFML/Config.hpp>

Button::Button(std::string text, sf::Font &font, float posX, float posY, float sizeX, float sizeY, int fontSize,
               sf::Color background, sf::Color textColor) {
    this->rectangleShape.setPosition(posX, posY);
    this->rectangleShape.setSize(sf::Vector2f{sizeX, sizeY});
    this->rectangleShape.setFillColor(background);
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4
    this->text.setFillColor(textColor);
#else
    this->text.setColor(textColor);
#endif
    this->text.setString(text);
    this->text.setFont(font);
    this->text.setCharacterSize(static_cast<unsigned int>(fontSize));
    auto boundingRect = this->text.getGlobalBounds();
    float textX = posX + (sizeX - boundingRect.width) * 0.5f;
    float textY = posY + (sizeY - boundingRect.height) * 0.5f;
    this->text.setPosition(textX, textY);
}

void Button::render(sf::RenderWindow &window) {
    window.draw(this->rectangleShape);
    window.draw(this->text);
}

auto Button::contains(float x, float y) -> bool {
    return this->rectangleShape.getGlobalBounds().contains(x,y);
}
