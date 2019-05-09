#pragma once

#include "Entity.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

// inherits indirectly SceneNode
class Aircraft : public Entity {
public:
    enum class Type {
        Eagle,
        Raptor,
    };

    Aircraft(Type type, const TextureHolder& textures);

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    Type mType;
    sf::Sprite mSprite;
};
