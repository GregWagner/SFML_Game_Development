#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <memory>
#include <vector>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;

    SceneNode();

    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);

    void update(sf::Time deltaTime);

    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void updateCurrent(sf::Time deltaTime);
    void updateChildren(sf::Time deltaTime);

    std::vector<Ptr> mChildren;
    SceneNode* mParent { nullptr };
};
