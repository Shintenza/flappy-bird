#include "../../include/Button.hpp"


Button::Button(sf::Vector2f& _mousePos,sf::Vector2f _size, sf::Vector2f _position, std::string& _assetsPath, sf::Color _color, std::string _content, int _charSize, bool _outline) :
    mousePos(_mousePos)
{
    size = _size;
    position = _position;
    assetsPath = _assetsPath;
    color = _color;
    outline = _outline;
    charSize = _charSize;
    content = _content;

    loadFont();
    init();
}
Button::~Button() {
    // printf("Siema jestem deleted\n");
}
Button::operator bool() const {
    if(button.getGlobalBounds().contains(mousePos)) {
        return true;
    }
    return false;
}
void Button::init() {
    button.setPosition(position);
    button.setSize(size);
    button.setFillColor(color);
    
    text.setPosition(position.x + button.getGlobalBounds().width / 2  - text.getGlobalBounds().width / 2, position.y + button.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2 );
}

void Button::loadFont() {
    if (!font.loadFromFile(assetsPath+"font1.ttf")) {
        log(2, "failed to load main font");
        exit(1);
    }
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setString(content);
    if (outline) {
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2);
    }
}

void Button::draw(sf::RenderTarget* window) {
    window->draw(button);
    window->draw(text);
}
sf::Vector2f Button::getEndYPosition() {
    return sf::Vector2f(position.x, position.y + size.y);
}
