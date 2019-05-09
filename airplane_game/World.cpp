#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mTextures()
    , mSceneGraph()
    , mSceneLayers()
    , mWorldBounds(0.0f, 0.0f, mWorldView.getSize().x, 2000.0f)
    , mSpawnPosition(mWorldView.getSize().x / 2.0f, mWorldBounds.height - mWorldView.getSize().y / 2.0f)
{
    loadTextures();
    buildScene();

    // prepare the view
    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time deltaTime)
{
    // scroll the world
    mWorldView.move(0.0f, mScrollSpeed * deltaTime.asSeconds());

    // move the player sideways
    sf::Vector2f position = mPlayerAircraft->getPosition();
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    // if player touches any border, flip is x velocity
    if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150) {
        velocity.x = -velocity.x;
        mPlayerAircraft->setVelocity(velocity);
    }
    // apply the movements
    mSceneGraph.update(deltaTime);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
    mTextures.load(Textures::ID::Eagle, "Media/Textures/Eagle.png");
    mTextures.load(Textures::ID::Raptor, "Media/Textures/Raptor.png");
    mTextures.load(Textures::ID::Desert, "Media/Textures/Desert.png");
}

void World::buildScene()
{
    // initialize the different layers
    for (std::size_t i {}; i < static_cast<std::size_t>(Layer::LayerCount); ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // prepare the tiled background
    sf::Texture& texture = mTextures.get(Textures::ID::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    // add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // add player's aircraft
    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Eagle, mTextures));
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(40.0f, mScrollSpeed);
    mSceneLayers[Layer::Air]->attachChild(std::move(leader));

    // add two escorting aircrafts, placed relatively to the main plane
    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Type::Raptor, mTextures));
    leftEscort->setPosition(-80.0f, 50.0f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Type::Raptor, mTextures));
    rightEscort->setPosition(80.0f, 50.0f);
    mPlayerAircraft->attachChild(std::move(rightEscort));
}
