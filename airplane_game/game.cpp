#include "game.h"
#include <iostream>
#include <sstream>

const float Game::PLAYER_SPEED = 100.0f;
const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "SFML Application")
    , mIsMovingUp {}, mIsMovingDown {}, mIsMovingRight {}, mIsMovingLeft {}
    , mStatisticsNumberOfFrames {}
{
    if (!mTexture.loadFromFile("Media/Textures/Eagle.png")) {
        std::cerr << "Error loading textures\n";
    }
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.0f, 100.0f);

    mFont.loadFromFile("Media/Sansation.ttf");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.0f, 5.0f);
    mStatisticsText.setCharacterSize(10);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME) {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            processEvents();
            update(TIME_PER_FRAME);
        }
        updateStatistics(elapsedTime);
        render();
    }
}

/*
 * processEvents()
 *
 * Handles user input
 */
void Game::processEvents() {
    sf::Event event {};
    while (mWindow.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
        }
    }
}

/*
 * update()
 *
 * Updates the game logic
 */
void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    if (mIsMovingUp) {
        movement.y -= PLAYER_SPEED;
    }
    if (mIsMovingDown) {
        movement.y += PLAYER_SPEED;
    }
    if (mIsMovingLeft) {
        movement.x -= PLAYER_SPEED;
    }
    if (mIsMovingRight) {
        movement.x += PLAYER_SPEED;
    }
    mPlayer.move(movement * deltaTime.asSeconds());
}

/*
 * render()
 *
 */
void Game::render() {
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) {
        mIsMovingUp = isPressed;
    } else if (key == sf::Keyboard::S) {
        mIsMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        mIsMovingLeft = isPressed;
    } else if (key == sf::Keyboard::D) {
        mIsMovingRight = isPressed;
    }
}

void Game::updateStatistics(sf::Time elapsedTime) {
    std::ostringstream output;
    mStatisticsUpdateTime += elapsedTime;
    ++mStatisticsNumberOfFrames;

    if (mStatisticsUpdateTime > sf::seconds(1.0f)) {
        output << "Frame / Second = " << mStatisticsNumberOfFrames << '\n'
               << "Time /  Update = "
               << (mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumberOfFrames)
               << "us";

        mStatisticsText.setString(output.str());
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumberOfFrames = 0;
    }
}
