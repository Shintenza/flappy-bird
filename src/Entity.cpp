#include "include/Entity.hpp"

Entity::Entity(float _speed) {
    isDead = false;
    speed = _speed;
}
sf::FloatRect Entity::getBounding() const  {
    return sprite.getGlobalBounds();
}
sf::Sprite Entity::getSprite() const {
    return sprite;
}
