#include "include/Entity.hpp"
#include <iostream>

Entity::Entity(sf::Texture* _texture, float _speed) {
    isDead = false;
    speed = _speed;
    texture = _texture;
}
Entity::~Entity() {
    #if DEV_MODE == 1
    log(0, "entity destroyed");
    #endif
}
sf::FloatRect Entity::getBounding() const  {
    return sprite.getGlobalBounds();
}
sf::Sprite Entity::getSprite() const {
    return sprite;
}
