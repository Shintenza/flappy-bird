#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "MenuState.hpp"
#include <stack>
#include <sqlite3.h>
#include <ctime>

#include "State.hpp"
#include "DbHandler.hpp"
#include "main.hpp"

// Przykładowe użycie: klasa
class Game {
private:
    sf::VideoMode windowMode;
    sf::RenderWindow* window;
    sf::Event event;

    int session_start;

    DbHandler *dbHandler;

    std::string assetsFolderName = "assets";
    int argc;
    char** argv;
    
    std::stack<State*> states;

    sf::Clock dtClock;
    float dt;

    bool isOpen;
    bool started;
    
    void getStartSessionDate();
    void initState();
    void initVariables();
    void initWindow();

public:
    // Deklaracja: konstruktor
    Game(int argc, char** argv);
    // Deklaracja: destruktor
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

