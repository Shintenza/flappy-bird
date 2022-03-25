#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    std::string texturePath;
    sf::Texture texture;
    sf::Sprite sprite;

    void initVars();
    void loadTexture();
    void createSprite();
public:
    Player();
    sf::Sprite getSprite() const;
};
