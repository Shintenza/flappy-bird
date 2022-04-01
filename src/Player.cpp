#include "include/Player.hpp"
#include <iostream>
#include <cmath>

Player::Player(sf::Texture *texture) : Entity(40) {
    setSprite(texture);
    flapHeight = 100.f;
}
void Player::move(float x, float y) {
    velocity.x+= x;
    velocity.y+= y;
}

void Player::fall(const float& dt) {
    velocity.y += 981.f *dt;
}

bool Player::checkIfDead(sf::RectangleShape collision_box) {
    if (collision_box.getGlobalBounds().intersects(getBounding())) {
        isDead = true;
        std::cout<<"KiLL"<<std::endl;
    }
    return isDead;
}

void Player::flap(const float& dt) {
    velocity.y = -sqrtf(2.0f * 981.f *flapHeight);
}
void Player::setSprite(sf::Texture *texture) {
    sprite.setTexture(*texture);
    sprite.setScale(0.1f, 0.1f);
}

void Player::update(const float& dt) {
    fall(dt);
    sprite.move(velocity*dt);
}
void Player::render(sf::RenderTarget* window) {
    window->draw(sprite);
}
