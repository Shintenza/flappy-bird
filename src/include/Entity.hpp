#pragma once
#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Sprite sprite;
    bool isDead;
    float speed;
public:
    Entity(float speed);
    //TODO destructor;
    virtual ~Entity();
    sf::FloatRect getBounding() const;
    sf::Sprite getSprite() const;
    
    virtual void setSprite(sf::Texture* texturePtr) = 0;
    virtual bool checkIfDead(sf::RectangleShape object) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target) = 0;
};
