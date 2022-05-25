#pragma once
#include "State.hpp"
#include "MainMenu.hpp"
#include "StatsMenu.hpp"


class MenuState: public State {
    MainMenu main;
    StatsMenu stats;
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
