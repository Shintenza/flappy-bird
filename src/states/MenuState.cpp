#include "../include/MenuState.hpp" 
#include "../include/DbHandler.hpp"
#include <ctime>
#include <time.h>
#include <iostream>

#define BACKGROUND_TEXTURE_NAME "background"

MenuState::MenuState(sf::RenderWindow* _window, DbHandler* dbh, std::string assets_path, bool& started) : 
    State(_window, dbh, "MenuState"),
    main(assets_path, getWindow()->getSize(), mousePosView),
    stats(assets_path, getWindow()->getSize(), dbHandler->getBestScores(), isStatScreenActive),
    isGameStarted(started)
{
    init(assets_path);
}
MenuState::~MenuState() {
    printf("MENU STATE destructor\n");
}
void MenuState::updateMousePos() {
   mousePos = sf::Mouse::getPosition(*getWindow());
   mousePosView = getWindow()->mapPixelToCoords(mousePos);
}
void MenuState::init(std::string assetsFolderPath) {

    //TODO return null when didn't load
    loadTexture(BACKGROUND_TEXTURE_NAME, assetsFolderPath+BACKGROUND_TEXTURE_NAME".png");
    if (!getTexture(BACKGROUND_TEXTURE_NAME)) {
        log(2, "Failed to load bg image");
        exit(1);
    }

    backgroundSprite.setTexture(*getTexture(BACKGROUND_TEXTURE_NAME));

    
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

