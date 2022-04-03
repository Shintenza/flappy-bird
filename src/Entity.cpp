#include "include/Entity.hpp"
#include <iostream>

Entity::Entity(float _speed) {
    isDead = false;
    speed = _speed;
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
