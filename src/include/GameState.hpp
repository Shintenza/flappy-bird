#pragma once

#include "Player.hpp"
#include "State.hpp"
#include "Obstacle.hpp"

class GameState : public State {
private:
    Player* player;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite[2];
    sf::RectangleShape collision_box;
    sf::Font font;
    sf::Text text;
    sf::Clock gameClock;

    std::vector<Obstacle*> entities;

    bool isHeld;
    bool gameEnded;
    bool sentStartingMessage;
    bool readyToSpawnObstacle;

    float groundHeight;
    float distance;
    float backgroundMoveSpeed;

    int backgroundYOffset;
    int score;

    void loadFonts(std::string assetFolderPath);
    void loadBackground(std::string assetFolderPath);
    void moveBackground(const float& dt);
    void initCollisionBox();
    void spawnObstacles();
    void setScore();
    void restartGame();

    sf::Text getStartText();
    sf::Text getEndingText();
    sf::Text getScoreText();
public:
    GameState(sf::RenderWindow* window, std::string assetFolderPath);
    void handleInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
