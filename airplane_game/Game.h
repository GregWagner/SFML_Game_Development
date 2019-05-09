#pragma once
#include "World.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game : private sf::NonCopyable {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void updateStatistics(sf::Time elapsedTIme);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    static const sf::Time TIME_PER_FRAME;

    sf::RenderWindow mWindow;
    World mWorld;

    sf::Font mFont;
    sf::Text mStatisticsText {};
    sf::Time mStatisticsUpdateTime {};
    std::size_t mStatisticsNumberOfFrames {};
};
