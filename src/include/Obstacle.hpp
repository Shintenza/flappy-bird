#include "Entity.hpp"

class Obstacle : public Entity{
private:
    sf::Texture* texture;
    sf::Sprite bottom_sprite;
    sf::Sprite top_sprite;

    bool isDead;
    bool passed;

    float gapSize = 150;
    float groundHeight;
    float moveSpeed;

    sf::Vector2u windowSize;
    sf::Vector2f velocity;

    void move(const float& dt);
    void setPlacement();
public:
    Obstacle(sf::Texture* texture, sf::Vector2u _windowSize, float ground_h, float move_s);
    Obstacle(const Obstacle& other);
    ~Obstacle();

    void setSprite();
    bool checkIfDead(sf::RectangleShape object);
    bool checkIfPassed() const;
    void pass();
    bool isColliding(sf::FloatRect player);
    sf::Vector2f getPosition();

    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
