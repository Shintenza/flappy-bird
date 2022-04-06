#include "include/Obstacle.hpp"
#include <iostream>
#include <random>

Obstacle::Obstacle(sf::Texture* texture, sf::Vector2u _windowSize, float ground_h, float move_s) : Entity(40) {
    ground_height = ground_h;
    windowSize = _windowSize;
    moveSpeed = move_s;
    passed = false;

    setSprite(texture);
}
Obstacle::~Obstacle() {
    printf("i am kill\n");
}

void Obstacle::move(const float& dt) {
    top_sprite.move(-moveSpeed*dt, 0);
    bottom_sprite.move(-moveSpeed*dt, 0);
}
void Obstacle::setPlacement() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, windowSize.y - 200 - gapSize);

    int yOffset = distr(eng);

    top_sprite.setPosition(windowSize.x + (top_sprite.getGlobalBounds().width), yOffset);
    bottom_sprite.setPosition(windowSize.x, yOffset + gapSize);
}
void Obstacle::setSprite(sf::Texture* texture) {
    bottom_sprite.setTexture(*texture, false);
    bottom_sprite.setScale(4.f, 5.f);

    top_sprite.setTexture(*texture);
    top_sprite.setScale(4.f, 5.f);
    top_sprite.setRotation(180.f);

    setPlacement();
}
bool Obstacle::checkIfDead(sf::RectangleShape collision_box) {
    if (bottom_sprite.getPosition().x + bottom_sprite.getGlobalBounds().width < 0)  {
        isDead = true;
        return true;
    }
    return false;
}
bool Obstacle::checkIfPassed() const {
    return passed;
}
void Obstacle::pass() {
    passed = true;
}
bool Obstacle::isColliding(sf::FloatRect player) {
    if (bottom_sprite.getGlobalBounds().intersects(player) || top_sprite.getGlobalBounds().intersects(player)) {
        return true;
    }
    return false;
}
sf::Vector2f Obstacle::getPosition() {
    return top_sprite.getPosition();
}
void Obstacle::update(const float& dt) {
    move(dt);

}
void Obstacle::render(sf::RenderTarget* window) {
    window->draw(bottom_sprite);
    window->draw(top_sprite);
}

