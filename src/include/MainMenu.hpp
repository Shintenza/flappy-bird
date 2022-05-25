#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Button.hpp"

class MainMenu {
private:
    sf::Font font;
    sf::Text gameTitle;
    sf::Text startGameText;
    sf::Text quitGameText;
    sf::Text checkStatsText;

    sf::Vector2f& mousePosView;

    sf::RectangleShape menuBox;
    sf::RectangleShape startGameButton; 
    sf::RectangleShape quitGameButton; 
    sf::RectangleShape checkStatsButton;

    std::vector<Button*> buttons;

    void loadFonts(std::string& assetsFolderPath);
    void positionMenu(sf::Vector2u windowSize, std::string& assetsFolderPath);
    bool quit;
    bool isHeld;

public:
    MainMenu(std::string &assetsFolderPath, sf::Vector2u windowSize, sf::Vector2f& mousePosView);
    ~MainMenu();
    void handleInput(sf::Vector2f mousePosView, bool& isStatScreenActive, bool& isGameStarted);
    bool getQuit();
    void init(std::string& assetsFolderPath, sf::Vector2u windowSize);
    void draw(sf::RenderTarget* target);
};
