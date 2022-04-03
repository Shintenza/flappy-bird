#include "include/Player.hpp"
#include <iostream>
#include <cmath>

Player::Player(sf::Texture *texture, sf::Vector2u _windowSize) : Entity(40) {
    windowSize = _windowSize;
    setSprite(texture);
    flapHeight = 100.f;
    isFalling = false;

    unsigned xPos = 0.3 * windowSize.x - (sprite.getGlobalBounds().width / 2);
    unsigned yPos = 0.5 * windowSize.y - (sprite.getGlobalBounds().height / 2);
    sprite.setPosition(xPos, yPos);
}
Player::~Player() {
    std::cout<<"dead"<<std::endl;
}


void Player::move(float x, float y) {
    velocity.x+= x;
    velocity.y+= y;
}
void Player::startFalling() {
    isFalling = true;
}
void Player::fall(const float& dt) {
    if (velocity.y > 80)  {
        if (sprite.getRotation() < 90.f) {
            angle+=80.f;
        }
    } else {
        if (isFalling) {
            angle=0;
        }
    }

    if (isFalling) {
        velocity.y += 981.f *dt;
    }
}

bool Player::checkIfActive() {
    return isFalling;
}

bool Player::checkIfDead(sf::RectangleShape collision_box) {
    if (collision_box.getGlobalBounds().intersects(getBounding()) && isFalling) {
        isFalling = false;
        velocity.y = 0;
        velocity.x = -400;
    }
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) {
        isDead = true;
    }
    return isDead;
}

void Player::flap(const float& dt) {
    if (isFalling) {
        velocity.y = -sqrtf(2.0f * 981.f *flapHeight);
    }
}
void Player::setSprite(sf::Texture *texture) {
    sprite.setTexture(*texture);
    sprite.setScale(0.1f, 0.1f);
}

void Player::update(const float& dt) {
    fall(dt);
    sprite.move(velocity*dt);
    sprite.setRotation(angle*dt);
}
void Player::render(sf::RenderTarget* window) {
    window->draw(sprite);
}
