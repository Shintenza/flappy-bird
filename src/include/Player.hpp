#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Player : public Entity{ 
private:
    float flapHeight;

    bool isFalling;
    void setSprite(sf::Texture* texturePtr);
    void fall(const float& dt);
    float angle;
    bool isFlying;

    sf::RectangleShape hitbox;

    sf::Vector2f size;
    sf::Vector2u windowSize;
    sf::Vector2f velocity;
    sf::Vector2f position;
public:
    float width;
    float height;

    Player(sf::Texture *texture, sf::Vector2u _windowSize);
    ~Player();

    void hitboxHandler();
    void startFalling();
    void stopFalling();
    void move(float x, float y);
    void flap(const float& dt);
    sf::FloatRect getHitboxBounding();

    bool checkIfActive();
    bool checkIfDead (sf::RectangleShape collision_box);
    void update(const float& dt);
    void render(sf::RenderTarget* window);
};
