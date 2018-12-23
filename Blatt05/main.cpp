#include <SFML/Graphics.hpp>
#include <memory>

#include "View/StartScreen.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Flappy Wizard"/*, sf::Style::Fullscreen*/);

    std::map<view::ScreenResult, std::shared_ptr<view::Screen>> screenStateMachine;

    screenStateMachine.insert(std::pair<view::ScreenResult, std::shared_ptr<view::Screen>>(
            view::ScreenResult::START, std::make_shared<view::StartScreen>(window)));

    std::shared_ptr<view::Screen> activeScreen = screenStateMachine.at(view::ScreenResult::START);

    while (true) {
        auto nextScreen = activeScreen.get()->run();

        if(nextScreen == view::ScreenResult::EXIT) {
            break;
        }

        activeScreen = screenStateMachine.at(nextScreen);
    }


    window.close();
    return 0;
}
