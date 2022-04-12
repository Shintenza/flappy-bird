#pragma once
#include "State.hpp"

class MenuState: public State {
    sf::Font font;
    sf::Text gameTitle;
    sf::Text startGameText;
    sf::Text quitGameText;

    sf::Sprite backgroundSprite;
    sf::RectangleShape menuBox;
    sf::RectangleShape startGameButton; 
    sf::RectangleShape quitGameButton; 

    sf::Vector2i mousePos;
    sf::Vector2f mousePosView;

    void updateMousePos();

    void init(std::string assetsFolderPath);
    void positionMenu();
public:
    MenuState(sf::RenderWindow* window, std::string assetFolderPath);

    void handleInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};
