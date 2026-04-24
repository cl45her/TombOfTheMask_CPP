#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Vector2f position;
public:
    virtual ~Entity() = default;
    
    
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    void setPosition(sf::Vector2f pos) { position = pos; }
    sf::Vector2f getPosition() const { return position; }
};

#endif