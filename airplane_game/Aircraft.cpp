#include "Aircraft.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Textures::ID toTextureID(Aircraft::Type type)
{
    switch (type) {
    case Aircraft::Type::Eagle:
        return Textures::ID::Eagle;
    case Aircraft::Type::Raptor:
        return Textures::ID::Raptor;
    }
    return Textures::ID::Eagle;
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
    : mType(type)
    , mSprite(textures.get(toTextureID(type)))
{
    // center the orgin
    sf::FloatRect bounds = mSprite.getLocalBounds(); // without any sprit transformations
    mSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
