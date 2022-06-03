#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "main.hpp"

class Player : public Entity { 
private:
    float flapHeight;

    bool isFalling;
    bool isFlying;
    void fall(const float& dt);
    float angle;
    float startX;
    float startY;

    unsigned &flapCount;

    sf::RectangleShape hitbox;

    sf::Vector2f size;
    sf::Vector2u windowSize;
    sf::Vector2f velocity;
    sf::Vector2f position;

    void setSprite();
public:
    float width;
    float height;

    Player(sf::Texture *texture, sf::Vector2u _windowSize, unsigned& flap_count);
    ~Player();

    void startFalling();
    void stopFalling(const float& dt);
    void move(float x, float y);
    void flap(const float& dt);
    void restartPlayer();
    sf::FloatRect getHitboxBounding();

    bool checkIfActive();
    bool checkIfDead (sf::RectangleShape collision_box);
    void update(const float& dt);
    void render(sf::RenderTarget* window);
};
