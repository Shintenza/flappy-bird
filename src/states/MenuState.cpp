#include "../include/MenuState.hpp" 
#include "../include/DbHandler.hpp"
#include <ctime>
#include <time.h>
#include <iostream>

#define BACKGROUND_TEXTURE_NAME "background"

MenuState::MenuState(sf::RenderWindow* _window, DbHandler* dbh, std::string assets_path, bool& started) : 
    State(_window, dbh, "MenuState"),
    stats(assets_path, getWindow()->getSize(), dbh, isStatScreenActive, mousePosView),
    main(assets_path, getWindow()->getSize(), mousePosView, stats),
    isGameStarted(started)
{
    init(assets_path);
}
MenuState::~MenuState() {
    #if DEV_MODE == 1
    log(0, "MenuState destroyed");
    #endif
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

    main.handleInput(mousePosView, isStatScreenActive, isGameStarted);
    stats.handleInput(mousePosView);

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

