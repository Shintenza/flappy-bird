#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool isDead;

    void setSprite(sf::Texture *texture);
    void fall(const float& dt);
public:
    Player(sf::Texture *texture);
    void move(const float& dt, int x, int y);
    void flap(const float& dt);
    bool checkIfDead (sf::RectangleShape& collision_box);
    sf::FloatRect getBouding() const;

    void update(const float& dt);
    void render(sf::RenderTarget* window);
};
