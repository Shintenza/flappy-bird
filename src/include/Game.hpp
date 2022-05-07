#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "MenuState.hpp"
#include <stack>
#include <sqlite3.h>
#include <ctime>

#include "State.hpp"
#include "DbHandler.hpp"

class Game {
private:
    sf::VideoMode windowMode;
    sf::RenderWindow* window;
    sf::Event event;

    std::time_t session_start;

    DbHandler *dbHandler;

    std::string assetsFolderName = "assets";
    int argc;
    char** argv;
    
    std::stack<State*> states;

    sf::Clock dtClock;
    float dt;

    unsigned highestScore;
    unsigned numberOfTries;
    unsigned flapCount;
    unsigned obstaclesCount;

    bool isOpen;
    bool started;
    
    void getStartSessionDate();
    void initState();
    void initVariables();
    void initWindow();

public:
    Game(int argc, char** argv);
    ~Game();
    void updateDt();
    void updatePollEvenets();
    void inputUpdate();

    std::string getAssetsPath();
    void getBestScore();

    bool isWindowOpen() const;
    sf::Vector2u getWindowSize() const;
    void update();
    void render();
};

