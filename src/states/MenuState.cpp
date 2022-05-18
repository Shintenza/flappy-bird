#include "../include/MenuState.hpp" 
#include "../include/DbHandler.hpp"
#include <ctime>
#include <time.h>
#include <iostream>

MenuState::MenuState(sf::RenderWindow* _window, DbHandler* dbh, std::string assets_path, bool& started) 
    : State(_window, dbh, "MenuState"), stats(dbHandler->getBestScores(), isStatScreenActive), isGameStarted(started)
{
    init(assets_path);
}
void MenuState::updateMousePos() {
   mousePos = sf::Mouse::getPosition(*getWindow());
   mousePosView = getWindow()->mapPixelToCoords(mousePos);
}
void MenuState::init(std::string assetsFolderPath) {

    loadTexture("BACKGROUND", assetsFolderPath+"background.png");
    if (!getTexture("BACKGROUND")) {
        std::cout<<"Failed to load bg image"<<std::endl;
        exit(1);
    }

    backgroundSprite.setTexture(*getTexture("BACKGROUND"));

    main.init(assetsFolderPath, getWindow()->getSize());
    stats.init(assetsFolderPath, getWindow()->getSize());
    
    isHeld = false;
}
void MenuState::handleInput(const float& dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        endState();
    }
}
void MenuState::update(const float& dt) {
    updateMousePos();
    handleInput(dt);

    stats.handleInput(mousePosView);
    main.handleInput(mousePosView, isStatScreenActive, isGameStarted);

    if (main.getQuit()) {
        endState();
    }
}
void MenuState::render(sf::RenderTarget* window) {
    window->draw(backgroundSprite);
    if (!isStatScreenActive) {
        main.draw(window);
    } else {
        stats.draw(window);
    }
    
}

// MainMenu struct

// StatsScreen

