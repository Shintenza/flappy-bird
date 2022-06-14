#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Button.hpp"
#include "main.hpp"
#include "StatsMenu.hpp"

class MainMenu {
private:
    sf::Font font;
    sf::Text gameTitle;

    StatsMenu& statsMenu;
    sf::Vector2f& mousePosView;

    sf::RectangleShape menuBox;

    std::vector<Button*> buttons;

    void loadFonts(std::string& assetsFolderPath);
    void positionMenu(sf::Vector2u windowSize, std::string& assetsFolderPath);
    bool quit;
    bool isHeld;

public:
    MainMenu(std::string &assetsFolderPath, sf::Vector2u windowSize, sf::Vector2f& mousePosView, StatsMenu& _statsMenu);
    ~MainMenu();
    void handleInput(sf::Vector2f mousePosView, bool& isStatScreenActive, bool& isGameStarted);
    bool getQuit();
    void init(std::string& assetsFolderPath, sf::Vector2u windowSize);
    void draw(sf::RenderTarget* target);
};
