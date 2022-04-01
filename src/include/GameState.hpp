#ifndef GAME_HPP
#define GAME_HPP

#include "State.hpp"
#include "Player.hpp"

class GameState : public State {
private:
    Player* player;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite[2];
    sf::RectangleShape collision_box;

    std::vector<Entity*> entities;

    bool isHeld;
    int backgroundYOffset;
    void loadBackground();
    void moveBackground();
    void initCollisionBox();

public:
    GameState(sf::RenderWindow* window);
    void handleInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
#endif
