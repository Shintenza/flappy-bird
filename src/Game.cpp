#include "include/Game.hpp"

void Game::initVariables() {
    windowMode = sf::VideoMode(800,600);
    gameEnded = false;
    isOpen = true;
    player = new Player();
}
void Game::initWindow() {
    window = new sf::RenderWindow(windowMode, "Flappy Bird");
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(false);
}
Game::Game() {
    initVariables();
    initWindow();
}
Game::~Game() {
    delete player;
}
void Game::updatePollEvenets() {
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            isOpen = false;
            window->close();
        }
    }
}
bool Game::isWindowOpen() const {
    return isOpen;
}
void Game::update(){
    updatePollEvenets();
}
void Game::render(){
    window->clear(sf::Color::Black);
    window->draw(player->getSprite());
    window->display();
}
