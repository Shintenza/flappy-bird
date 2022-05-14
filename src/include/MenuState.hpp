#pragma once
#include "State.hpp"

struct MainMenu {
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
    void draw(sf::RenderTarget* target);
};

struct StatsScreen {
    sf::Font font;
    sf::Text header;
    sf::Text bestScoresHeader;
    sf::Text bestScoresText;
    sf::Text secondaryStatsHeader;
    sf::Text secondaryStats;
    void positionMenu(sf::Vector2u windowSize, std::vector<bestScores> scores);

    void loadFonts(std::string& assetsFolderPath);
    void draw(sf::RenderTarget* target);
};

class MenuState: public State {
    MainMenu main;
    StatsScreen stats;
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

    void handleInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
