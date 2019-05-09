#include "Game.h"
#include <iostream>

#include <SFML/Window/Event.hpp>

const sf::Time Game::TIME_PER_FRAME { sf::seconds(1.0f / 60.0f) };

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "World", sf::Style::Close)
    , mWorld(mWindow)
    , mFont()
{
    mFont.loadFromFile("Media/Sansation.ttf");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.0f, 5.0f);
    mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        // always call update at a fixed time interval
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

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    mWorld.update(deltaTime);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
}

void Game::updateStatistics(sf::Time elapsedTIme)
{
    mStatisticsUpdateTime += elapsedTIme;
    ++mStatisticsNumberOfFrames;
    if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
        std::string s = "Frames / Second = " + std::to_string(mStatisticsNumberOfFrames) + '\n';
        s += "Time / Update = " + std::to_string(mStatisticsUpdateTime.asMilliseconds() / mStatisticsNumberOfFrames) + "us";
        mStatisticsText.setString(s);
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumberOfFrames = 0;
    }
}
