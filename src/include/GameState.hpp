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
    sf::Font font;
    sf::Text text;

    std::vector<Entity*> entities;

    bool isHeld;
    bool gameEnded;
    bool sentStartingMessage;
    int backgroundYOffset;

    void loadFonts();
    void loadBackground();
    void moveBackground();
    void initCollisionBox();

    sf::Text getStartText();
    sf::Text getEndingText();
public:
    GameState(sf::RenderWindow* window);
    void handleInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
#endif
