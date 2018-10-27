#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void updateStatistics(sf::Time elapsedTime);

        sf::RenderWindow mWindow;
        sf::Texture mTexture;
        sf::Sprite mPlayer;

        static const float PLAYER_SPEED;
        static const sf::Time TIME_PER_FRAME;

        bool mIsMovingUp;
        bool mIsMovingDown;
        bool mIsMovingRight;
        bool mIsMovingLeft;

        sf::Font mFont;
        sf::Text mStatisticsText;
        std::size_t mStatisticsNumberOfFrames;
        sf::Time mStatisticsUpdateTime;
};

#endif
