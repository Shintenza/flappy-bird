#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Player : public Entity{ 
private:
    float flapHeight;
    void setSprite(sf::Texture* texturePtr);
    void fall(const float& dt);

    sf::Vector2f velocity;
public:
    Player(sf::Texture *texture);

    void move(float x, float y);
    void flap(const float& dt);

    bool checkIfDead (sf::RectangleShape collision_box);
    void update(const float& dt);
    void render(sf::RenderTarget* window);
};
