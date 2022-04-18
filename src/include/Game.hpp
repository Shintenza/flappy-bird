#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "MenuState.hpp"
#include <stack>

#include "State.hpp"

class Game {
private:
    sf::VideoMode windowMode;
    sf::RenderWindow* window;
    sf::Event event;

    std::string assetsFolderName = "assets";
    int argc;
    char** argv;
    
    std::stack<State*> states;

    sf::Clock dtClock;
    float dt;

    bool isOpen;
    bool started;
    
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

    bool isWindowOpen() const;
    sf::Vector2u getWindowSize() const;
    void update();
    void render();
};

