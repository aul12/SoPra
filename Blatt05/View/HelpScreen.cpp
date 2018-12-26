/**
 * @file HelpScreen.cpp
 * @author paul
 * @date 23.12.18
 * @brief HelpScreen implementation
 */

#include <fstream>
#include "HelpScreen.hpp"

namespace view {
    HelpScreen::HelpScreen(sf::RenderWindow &renderWindow) : Screen(renderWindow) {
        if(!font.loadFromFile("../Res/harry_p.ttf")) {
            throw std::runtime_error("Could not load font");
        }

        auto size = renderWindow.getSize();
        backButton = Button{"Back", font, size.x*0.1f, size.y - 70.0f, size.x*0.8f, 50};

        helpText.setFont(font);
        helpText.setCharacterSize(30);
        helpText.setPosition(size.x*0.1f,30);
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4 // Travis uses some ancient version of sfml
        helpText.setFillColor(sf::Color::Black);
#else
        helpText.setColor(sf::Color::Black);
#endif
        std::ifstream helpStream("../Res/Help.txt");
        std::string helpString(std::istreambuf_iterator<char>(helpStream), {});
        helpText.setString(helpString);
    }

    auto HelpScreen::run(std::map<ScreenResult, std::shared_ptr<Screen>> &screens) -> std::shared_ptr<Screen> {
        while (this->renderWindow.isOpen()) {
            sf::Event event{};
            while (renderWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        return screens.at(ScreenResult::EXIT);
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (backButton.contains(event.mouseButton.x, event.mouseButton.y)) {
                                return screens.at(ScreenResult::START);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            renderWindow.clear(sf::Color{0xEC, 0xB9, 0x39, 255}); // Color stolen from: http://harrypotter.wikia.com/wiki/Hufflepuff
            backButton.render(renderWindow);
            renderWindow.draw(helpText);

            renderWindow.display();
        }
        return screens.at(ScreenResult::EXIT);
    }
}
