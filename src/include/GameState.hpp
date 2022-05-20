#pragma once
#include <algorithm>

#include "Player.hpp"
#include "State.hpp"
#include "Obstacle.hpp"

struct Background {
    sf::Sprite backgroundSprite[2];
    sf::Sprite groundSprite[2];
};

class GameState : public State {
private:
    Player* player;

    sf::Texture backgroundTexture;
    sf::Texture groundTexture;
    Background background;

    sf::RectangleShape collision_box;
    sf::Font font;
    sf::Text text;
    sf::Text s_text;
    sf::Text best_scores;
    sf::Clock gameClock;

    std::vector<Obstacle*> entities;
    std::vector<int> lastSessionScores;

    bool isHeld;
    bool gameEnded;
    bool sentStartingMessage;
    bool readyToSpawnObstacle;
    
    float groundHeight;
    float distance;
    float backgroundMoveSpeed;

    int backgroundYOffset;
    unsigned score;
    unsigned &highestScore;
    unsigned &numberOfTries;
    unsigned &flapCount;
    unsigned &obstacleCount;

    void loadFonts(std::string assetFolderPath);
    void loadBackground(std::string assetFolderPath);
    void moveBackground(const float& dt);
    void initCollisionBox();
    void spawnObstacles();
    void setScore();
    void restartGame();

    void updateLastScores(unsigned& score);

    
    sf::Text getStartText();
    sf::Text getBestScore();
    sf::Text getBestSessionScores();
    std::array<sf::Text, 2> getEndingText();
    sf::Text getScoreText();
public:
    GameState(sf::RenderWindow* window, DbHandler *dbH, std::string assetFolderPath, unsigned& highest_score, 
            unsigned& number_of_tries, unsigned& flap_count, unsigned& obstacle_count);
    void handleInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
