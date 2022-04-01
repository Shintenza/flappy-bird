#include "include/Game.hpp"
#include "include/GameState.hpp"
#include "include/Player.hpp"
#include <iostream>

void Game::initState () {
    states.push(new GameState(window));
}
void Game::initVariables() {
    windowMode = sf::VideoMode(800,600);
    isOpen = true;
}

void Game::initWindow() {
    window = new sf::RenderWindow(windowMode, "Flappy Bird");
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(false);
};
Game::Game() {
    initVariables();
    initWindow();
    initState();
}
Game::~Game() {
    delete window;
}
void Game::updateDt(){
    dt = dtClock.restart().asSeconds();
}
void Game::updatePollEvenets() {
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            isOpen = false;
            window->close();
        }
    }
}
void Game::inputUpdate() {
}
bool Game::isWindowOpen() const {
    return isOpen;
}
sf::Vector2u Game::getWindowSize() const {
    return window->getSize();
}
void Game::update(){
    updatePollEvenets();
    if(states.size()>0) {
        states.top()->update(dt);
    }
}
void Game::render(){
    window->clear();

    if (states.size() > 0) {
        states.top()->render(window);
    }
    window->display();
}
