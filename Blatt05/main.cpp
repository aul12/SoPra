#include <SFML/Graphics.hpp>

#include "Util/Vector.hpp"
#include "Util/Rectangle.hpp"
#include "Controller/Environment.hpp"

int main() {
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/

    controller::Environment environment{"../config.json"};
    while(true) {
        environment.update(1);
    }

    return 0;
}
