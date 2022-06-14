#pragma once
#include <SFML/Graphics.hpp>
#include "utils/logging.hpp"
#include "main.hpp"

#define FONT_NAME "font2"

class Button {
private:
    std::string content;
    std::string assetsPath;

    sf::Font font;
    sf::Text text;

    sf::Vector2f& mousePos;
    sf::RectangleShape button;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Color color;
    int charSize;
    bool outline;

    void init ();
    void loadFont();
public:
    explicit operator bool() const;
    Button(sf::Vector2f& mousePos, sf::Vector2f size, sf::Vector2f position, std::string& _assetsPath, sf::Color color, std::string content, int charSize, bool outline);
    Button(const Button& btn);
    ~Button();
    void draw(sf::RenderTarget* window);
    sf::Vector2f getEndYPosition();
};
