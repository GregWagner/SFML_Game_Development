#pragma once

#include "Aircraft.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "SpriteNode.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <array>

// forward declaraion
namespace sf {
class RenderWindow;
}

class World : private sf::NonCopyable {
public:
    explicit World(sf::RenderWindow& window);
    void update(sf::Time deltaTime);
    void draw();

private:
    void loadTextures();
    void buildScene();

    enum Layer {
        Background,
        Air, // entities in the air
        LayerCount, // total number of layers (keep last)
    };

    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;
    SceneNode mSceneGraph;
    std::array<SceneNode*, static_cast<size_t>(Layer::LayerCount)> mSceneLayers;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed { -50.0f };
    Aircraft* mPlayerAircraft { nullptr };
};
