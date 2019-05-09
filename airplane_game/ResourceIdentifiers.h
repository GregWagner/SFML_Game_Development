#pragma once

// forward declaration
namespace sf {
class Texture;
}

namespace Textures {
enum class ID {
    Eagle,
    Raptor,
    Desert,
};}

// forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
