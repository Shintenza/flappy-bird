#pragma once 

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game {
private:
    sf::VideoMode windowMode;
    sf::RenderWindow* window;
    sf::Event event;
    bool gameEnded;
    bool isOpen;
    Player *player;

    void initVariables();
    void initWindow();
public:
    Game();
    ~Game();

    void updatePollEvenets();
    bool isWindowOpen() const;
    void update();
    void render();
};

