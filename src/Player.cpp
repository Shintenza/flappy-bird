#include "include/Player.hpp"
#include <iostream>

Player::Player(sf::Texture *texture){
    speed = 40;
    setSprite(texture);
    isDead = true;
}
void Player::move(const float& dt, int x, int y) {
    sprite.move(x*speed*dt, y*speed*dt);
}
void Player::fall(const float& dt) {
    sprite.move(0, 11*speed*dt);
}
bool Player::checkIfDead(sf::RectangleShape& collision_box) {
    if (collision_box.getGlobalBounds().intersects(getBouding())) {
        isDead = true;
        std::cout<<"KiLL"<<std::endl;
    }
    return isDead;
}
void Player::flap(const float& dt) {
    sprite.move(0, -40*speed*dt);
}
void Player::setSprite(sf::Texture *texture) {
    sprite.setTexture(*texture);
    sprite.setScale(0.1f, 0.1f);
}
sf::FloatRect Player::getBouding() const {
    return sprite.getGlobalBounds();
}
void Player::update(const float& dt) {
    fall(dt);
}
void Player::render(sf::RenderTarget* window) {
    window->draw(sprite);
}
