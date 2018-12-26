/**
 * @file Button.cpp
 * @author paul
 * @date 23.12.18
 * @brief Implementation of the Button class
 */

#include "Button.hpp"

#include <SFML/Config.hpp>

Button::Button(std::string caption, sf::Font &font, float posX, float posY, float sizeX, float sizeY, int fontSize,
               sf::Color background, sf::Color textColor) {
    this->rectangleShape.setPosition(posX, posY);
    this->rectangleShape.setSize(sf::Vector2f{sizeX, sizeY});
    this->rectangleShape.setFillColor(background);
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4 // Travis uses some ancient version of sfml
    this->text.setFillColor(textColor);
#else
    this->text.setColor(textColor);
#endif
    this->text.setString(caption);
    this->text.setFont(font);
    this->text.setCharacterSize(static_cast<unsigned int>(fontSize));
    auto boundingRect = this->text.getGlobalBounds();
    float textX = posX + (sizeX - boundingRect.width) * 0.5f;
    /*
     * Don't mind the 0.8, this is just because the bounding rect calculation of SFML is not very accurate.
     * See: https://www.sfml-dev.org/documentation/2.4.0/classsf_1_1Shape.php#a5257341fe832884dbba6b9dc855e33cc
     * "This function does not necessarily return the minimal bounding rectangle.
     * It merely ensures that the returned rectangle covers all the vertices (but possibly more).
     * This allows for a fast approximation of the bounds as a first check;
     * you may want to use more precise checks on top of that."
     */
    float textY = posY + (sizeY*0.8f - boundingRect.height) * 0.5f;
    this->text.setPosition(textX, textY);
}

auto Button::contains(float x, float y) -> bool {
    return this->rectangleShape.getGlobalBounds().contains(x,y);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->rectangleShape, states);
    target.draw(this->text,states);
}
