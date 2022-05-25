#pragma once
#include <SFML/Graphics.hpp>
#include "DbHandler.hpp"
#include "Button.hpp"

class StatsMenu {
private:
    sf::Font font;
    sf::Text header;
    sf::Text bestScoresHeader;
    sf::Text bestScoresText;
    sf::Text secondaryStatsHeader;
    sf::Text secondaryStats;

    sf::Vector2f& mousePos;

    void positionMenu(std::string& assetsFolderPath, sf::Vector2u windowSize);
    
    Button *goBack;
    DbHandler* dbHandler;
    
    void loadFonts(std::string& assetsFolderPath);
    void init(std::string& assetsFolderPath, sf::Vector2u windowSize);

    bool& active;
    bool isHeld;
public:
    StatsMenu(std::string& assetsPath, sf::Vector2u windowSize, DbHandler* dbHandler, bool& isStatScreenActive, sf::Vector2f& mousePos);
    ~StatsMenu();
    bool isActive();
    void handleInput(sf::Vector2f mousePosView);
    void draw(sf::RenderTarget* target);
};

