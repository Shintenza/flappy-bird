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

    sf::Vector2u windowSize;
    sf::Vector2f velocity;
public:
    Player(sf::Texture *texture, sf::Vector2u _windowSize);
    ~Player();

    void startFalling();
    void move(float x, float y);
    void flap(const float& dt);

    bool checkIfActive();
    bool checkIfDead (sf::RectangleShape collision_box);
    void update(const float& dt);
    void render(sf::RenderTarget* window);
};
