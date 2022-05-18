#pragma once
#include <SFML/Graphics.hpp>
#include "DbHandler.hpp"

struct StatsScreen {
private:
    sf::Font font;
    sf::Text header;
    sf::Text bestScoresHeader;
    sf::Text bestScoresText;
    sf::Text secondaryStatsHeader;
    sf::Text secondaryStats;
    sf::Text buttonText;


    std::vector<bestScores> scores;

    void positionMenu(sf::Vector2u windowSize);

    sf::RectangleShape goBackButton;

    void loadFonts(std::string& assetsFolderPath);

    bool& active;
    bool isHeld;
public:
    StatsScreen(std::vector<bestScores> given_scores, bool& isStatScreenActive);
    bool isActive();
    void handleInput(sf::Vector2f mousePosView);
    void init(std::string& assetsFolderPath, sf::Vector2u windowSize);
    void draw(sf::RenderTarget* target);
};

