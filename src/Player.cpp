#include "include/Player.hpp"
#include <iostream>

void Player::initVars() {
   texturePath = "./../assets/bird.png";
}
void Player::loadTexture() {
    if (!texture.loadFromFile("./assets/bird.png")) {
        std::cout<<"PLAYER::Unable to load a texture"<<std::endl;
        exit(1);
    }
}
void Player::createSprite() {
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
}
Player::Player() {
    loadTexture();
    createSprite();
}
sf::Sprite Player::getSprite() const {
    return sprite;
}
