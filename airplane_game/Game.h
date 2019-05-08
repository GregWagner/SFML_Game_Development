#pragma once

#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable {
public:
    Game();
    void run();

private:
    static const float PLAYER_SPEED;
    static const sf::Time TIME_PER_FRAME;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void updateStatistics(sf::Time elapsedTIme);

    sf::RenderWindow mWindow;
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    sf::Font mFont;
    sf::Text mStatisticsText {};
    sf::Time mStatisticsUpdateTime {};

    std::size_t mStatisticsNumberOfFrames;

    bool mIsMovingUp {};
    bool mIsMovingDown {};
    bool mIsMovingRight {};
    bool mIsMovingLeft {};
};
