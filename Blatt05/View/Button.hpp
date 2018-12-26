/**
 * @file Button.hpp
 * @author paul
 * @date 23.12.18
 * @brief Declaration of the Button class
 */

#ifndef BUTTON_HPP
#define BUTTON_HPP


#include <SFML/Graphics.hpp>

/**
 * Implements an button for SFML, can be used like any other SFML drawable
 */
class Button : public sf::Drawable {
public:
    /**
     * Default constructor, all values are set to their default value (depending on the SFML Version nothing can be seen)
     */
    Button() = default;

    /**
     * Create an button, the text will be centered in the button
     * @param caption the string written on the Button
     * @param font the font of the text,
     * @param posX the absolute X-Position of the button (in pixel)
     * @param posY the absolute Y-Position of the button (in pixel)
     * @param sizeX the size of the Button in the X-Dimension (in pixel)
     * @param sizeY the size of the Button in the Y-Dimension (in pixel)
     * @param fontSize the size of the caption
     * @param background the color of the background
     * @param textColor the color of the caption
     */
    Button(std::string caption, sf::Font &font, float posX, float posY, float sizeX, float sizeY, int fontSize = 30,
            sf::Color background = sf::Color::Black, sf::Color textColor = sf::Color::White);

    /**
     * Check whether a point lies within the rectangle, useful to detect button clicks
     * @param x the absolute x position of the point to check (in pixel)
     * @param y the absolute y position of the point to check (in pixel)
     * @return true if the point lies within the button
     */
    auto contains(float x, float y) -> bool;

protected:
    /**
     * Implements the draw method required by the sf::Drawable interface
     * @param target the window on which to draw (or a RenderTexture)
     * @param states defines the states used for drawing to a RenderTarget
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Text text;
    sf::RectangleShape rectangleShape;
};


#endif
