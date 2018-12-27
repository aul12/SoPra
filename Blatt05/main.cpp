#include <SFML/Graphics.hpp>
#include <memory>
#include <fstream>
#include <iostream>

#include "View/StartScreen.hpp"
#include "View/HelpScreen.hpp"
#include "View/GameScreen.hpp"
#include "View/GameOverScreen.hpp"
#include "View/HighscoreScreen.hpp"
#include "View/ExitScreen.hpp"

#include "Controller/Config.hpp"

int main(int argc, char *argv[]) {
    std::string configFileName = (argc <= 1 ? "config.json" : argv[1]);

    controller::Config config{configFileName};


    sf::ContextSettings contextSettings{};
    contextSettings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode{1920,1080}, "Flappy Wizard", sf::Style::Fullscreen, contextSettings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    std::map<view::ScreenResult, std::shared_ptr<view::Screen>> screens;

    screens.insert(std::pair<view::ScreenResult, std::shared_ptr<view::Screen>>(
            view::ScreenResult::START, std::make_shared<view::StartScreen>(window, config.getResourceConfig())));
    screens.insert(std::pair<view::ScreenResult, std::shared_ptr<view::Screen>>(
            view::ScreenResult::HELP, std::make_shared<view::HelpScreen>(window, config.getResourceConfig())));
    screens.insert(std::pair<view::ScreenResult, std::shared_ptr<view::Screen>>(
            view::ScreenResult::GAME, std::make_shared<view::GameScreen>(window, config.getResourceConfig(),
                    config.getGameConfig())));
    screens.insert(std::pair<view::ScreenResult, std::shared_ptr<view::Screen>>(
            view::ScreenResult::GAME_OVER, std::make_shared<view::GameOverScreen>(window, config.getResourceConfig())));
    screens.insert(std::pair<view::ScreenResult, std::shared_ptr<view::Screen>>(
            view::ScreenResult::HIGHSCORE, std::make_shared<view::HighscoreScreen>(window, config.getResourceConfig())));
    screens.insert(std::pair<view::ScreenResult, std::shared_ptr<view::Screen>>(
            view::ScreenResult::EXIT, std::make_shared<view::ExitScreen>(window)));

    std::shared_ptr<view::Screen> activeScreen = screens.at(view::ScreenResult::START);

    while (window.isOpen()) {
        activeScreen = activeScreen->run(screens);
    }


    window.close();
    return 0;
}
