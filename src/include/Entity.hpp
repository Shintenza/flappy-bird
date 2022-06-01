#pragma once
#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Sprite sprite;
    bool isDead;
    float speed;
    sf::Texture* texture;
public:
    Entity(sf::Texture* _texture, float _speed);
    //TODO destructor;
    virtual ~Entity();
    sf::FloatRect getBounding() const;
    sf::Sprite getSprite() const;
    
    bool isColliding(sf::FloatRect player);

    virtual void setSprite() = 0;
    virtual bool checkIfDead(sf::RectangleShape object) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target) = 0;
};
