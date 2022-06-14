#pragma once
#include "State.hpp"
#include "MainMenu.hpp"
#include "StatsMenu.hpp"
#include "main.hpp"


class MenuState: public State {
    StatsMenu stats;
    MainMenu main;
    sf::Sprite backgroundSprite;

    sf::Vector2i mousePos;
    sf::Vector2f mousePosView;

    bool isHeld;
    bool& isGameStarted;
    bool isStatScreenActive;

    void updateMousePos();

    void init(std::string assetsFolderPath);
public:
    MenuState(sf::RenderWindow* window, DbHandler *dbH, std::string assetFolderPath, bool& started);
    ~MenuState();

    void handleInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
