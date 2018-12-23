#include <SFML/Graphics.hpp>

#include "View/StartScreen.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Flappy Wizard"/*, sf::Style::Fullscreen*/);
    view::StartScreen startScreen{window};
    while(startScreen.run() != view::ScreenResult::EXIT);

    window.close();
    return 0;
}
