#include "include/Player.hpp"
#include "include/utils/logging.hpp"
#include <iostream>
#include <cmath>

Player::Player(sf::Texture *_texture, sf::Vector2u _windowSize, unsigned& flap_count) : Entity(_texture, 40), flapCount(flap_count) {
    windowSize = _windowSize;
    setSprite();
    flapHeight = 70.f;
    isFalling = false;
    angle = 0;

    unsigned xPos = 0.3 * windowSize.x - (sprite.getGlobalBounds().width / 2);
    unsigned yPos = 0.5 * windowSize.y - (sprite.getGlobalBounds().height / 2);
    sprite.setPosition(xPos, yPos);

    size.x = sprite.getGlobalBounds().width;
    size.y = sprite.getGlobalBounds().height;
}

Player::~Player() {
    #if DEV_MODE == 1
    log(0, "player deleted");
    #endif
}

void Player::hitboxHandler() {
    hitbox.setSize(size);
    hitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y);
    hitbox.setFillColor(sf::Color::Blue);
}


void Player::move(float x, float y) {
    velocity.x+= x;
    velocity.y+= y;
}
void Player::startFalling() {
    isFalling = true;
}
void Player::stopFalling() {
    isFalling = false;
    velocity.x = -400;
}
void Player::fall(const float& dt) {
    if (isFalling) {
        velocity.y += 981.f *dt;
    }
}

sf::FloatRect Player::getHitboxBounding() {
    return hitbox.getGlobalBounds();
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
        angle = -10.f;
        flapCount++;
    }
}
void Player::restartPlayer() {
    unsigned xPos = 0.3 * windowSize.x - (sprite.getGlobalBounds().width / 2);
    unsigned yPos = 0.5 * windowSize.y - (sprite.getGlobalBounds().height / 2);
    sprite.setPosition(xPos, yPos);
    velocity = sf::Vector2f(0, 0);
    isFalling = false;
    isDead = false;
    sprite.setRotation(0);
    angle = 0;
}
void Player::setSprite() {
    sprite.setTexture(*texture);
    sprite.setScale(0.1f, 0.1f);
}

void Player::update(const float& dt) {
    fall(dt);

    if (sprite.getPosition().y < 0) {
        velocity.y = 50;
    }
    sprite.move(velocity*dt);
    sprite.setRotation(angle);
    

    hitboxHandler();

    
    if (velocity.y > 0) {
        float rotation = sprite.getRotation() > 180 ? sprite.getRotation() - 360.f : sprite.getRotation();
        if (rotation < 90) {
            angle += 100*dt;
        }
    }
}
void Player::render(sf::RenderTarget* window) {
    window->draw(sprite);
}
