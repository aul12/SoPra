#include <SFML/Graphics.hpp>

#include "Util/Vector.hpp"
#include "Util/Rectangle.hpp"
#include "Controller/Environment.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
