#include "include/Entity.hpp"
#include <iostream>

Entity::Entity(sf::Texture* _texture, float _speed) {
    isDead = false;
    speed = _speed;
    texture = _texture;
}
Entity::~Entity() {
    std::cout<<"destroyed"<<std::endl;
}
sf::FloatRect Entity::getBounding() const  {
    return sprite.getGlobalBounds();
}
sf::Sprite Entity::getSprite() const {
    return sprite;
}
