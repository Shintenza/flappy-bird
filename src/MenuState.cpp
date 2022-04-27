#include "include/MenuState.hpp"
#include <iostream>

MenuState::MenuState(sf::RenderWindow* _window, std::string assets_path, bool& started) : State(_window), isGameStarted(started){
    init(assets_path);
    positionMenu();
}
void MenuState::updateMousePos() {
   mousePos = sf::Mouse::getPosition(*getWindow());
   mousePosView = getWindow()->mapPixelToCoords(mousePos);
}
void MenuState::init(std::string assetsFolderPath) {
    if (!font.loadFromFile(assetsFolderPath+"font1.ttf")) {
        std::cout<<"Failed to load font1"<<std::endl;
        exit(1);
    }

    loadTexture("BACKGROUND", assetsFolderPath+"background.png");
    if (!getTexture("BACKGROUND")) {
        std::cout<<"Failed to load bg image"<<std::endl;
        exit(1);
    }
    backgroundSprite.setTexture(*getTexture("BACKGROUND"));
    positionMenu();

    isHeld = false;
    
}
void MenuState::positionMenu() {
    sf::Vector2u windowSize = getWindow()->getSize();
    sf::Vector2f menuBoxPosition;
    float height = windowSize.y*0.7f;
    float width = windowSize.x*0.7f;


    menuBox.setSize(sf::Vector2f(width, height));
    menuBox.setPosition(windowSize.x *.5f - width *.5f, windowSize.y * .5f - height *.5f);
    menuBox.setFillColor(sf::Color::Yellow);
    menuBoxPosition = menuBox.getPosition();
    
    gameTitle.setFont(font);
    gameTitle.setString("Flappy Bird");
    gameTitle.setCharacterSize(width*0.14f);
    gameTitle.setPosition(windowSize.x *.5f - gameTitle.getGlobalBounds().width * .5f, menuBoxPosition.y + 10);
    gameTitle.setOutlineThickness(2);
    gameTitle.setOutlineColor(sf::Color::Black);

    startGameButton.setSize(sf::Vector2f(width*.5f, height*.15f));
    startGameButton.setFillColor(sf::Color::Blue);
    startGameButton.setPosition(windowSize.x * 0.5f - startGameButton.getGlobalBounds().width * 0.5f, 
        gameTitle.getPosition().y + gameTitle.getGlobalBounds().height + 60);

    quitGameButton.setSize(sf::Vector2f(width*.5f, height*.15f));
    quitGameButton.setFillColor(sf::Color::Red);
    quitGameButton.setPosition(windowSize.x * 0.5f - quitGameButton.getGlobalBounds().width * 0.5f , startGameButton.getPosition().y + startGameButton.getSize().y + 40);

    startGameText.setString("Start");
    startGameText.setCharacterSize(width*0.09f);
    startGameText.setOutlineColor(sf::Color::Black);
    startGameText.setOutlineThickness(2);
    startGameText.setFont(font);

    quitGameText.setString("Quit");
    quitGameText.setCharacterSize(width*0.09f);
    quitGameText.setOutlineColor(sf::Color::Black);
    quitGameText.setOutlineThickness(2);
    quitGameText.setFont(font);

    startGameText.setPosition(windowSize.x *.5f - startGameText.getGlobalBounds().width *.5f, 
            startGameButton.getPosition().y + startGameButton.getSize().y *.5f - startGameText.getGlobalBounds().height);
    
    quitGameText.setPosition(windowSize.x *.5f - quitGameText.getGlobalBounds().width *.5f, 
            quitGameButton.getPosition().y + quitGameButton.getSize().y *.5f - quitGameText.getGlobalBounds().height);
}
void MenuState::handleInput(const float& dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        endState();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(!isHeld) {
            isHeld = true;
            if (quitGameButton.getGlobalBounds().contains(mousePosView)) {
                endState();
            }
            if (startGameButton.getGlobalBounds().contains(mousePosView)) {
                isGameStarted = true;
            }
        }
    } else {
        isHeld = false;
    }
}
void MenuState::update(const float& dt) {
    updateMousePos();
    handleInput(dt);
}
void MenuState::render(sf::RenderTarget* window) {
    window->draw(backgroundSprite);
    window->draw(menuBox);
    window->draw(gameTitle);
    window->draw(startGameButton);
    window->draw(quitGameButton);
    window->draw(startGameText);
    window->draw(quitGameText);
}
