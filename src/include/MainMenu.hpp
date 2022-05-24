#pragma once
#include <SFML/Graphics.hpp>

class MainMenu {
private:
    sf::Font font;
    sf::Text gameTitle;
    sf::Text startGameText;
    sf::Text quitGameText;
    sf::Text checkStatsText;

    sf::RectangleShape menuBox;
    sf::RectangleShape startGameButton; 
    sf::RectangleShape quitGameButton; 
    sf::RectangleShape checkStatsButton;

    void loadFonts(std::string& assetsFolderPath);
    void positionMenu(sf::Vector2u windowSize);
    bool quit;
    bool isHeld;

public:
    MainMenu(std::string &assetsFolderPath, sf::Vector2u windowSize);
    void handleInput(sf::Vector2f mousePosView, bool& isStatScreenActive, bool& isGameStarted);
    bool getQuit();
    void init(std::string& assetsFolderPath, sf::Vector2u windowSize);
    void draw(sf::RenderTarget* target);
};
