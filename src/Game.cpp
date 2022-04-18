#include "include/Game.hpp"
#include "include/GameState.hpp"
#include "include/Player.hpp"
#include "include/MenuState.hpp"
#include <iostream>

void Game::initState () {
    states.push(new MenuState(window, getAssetsPath(), started));
}
void Game::initVariables() {
    windowMode = sf::VideoMode(800,600);
    isOpen = true;
    started = false;
}

void Game::initWindow() {
    window = new sf::RenderWindow(windowMode, "Flappy Bird");
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(false);
};

Game::Game(int _argc, char **_argv) : argc(_argc), argv(_argv) {
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

std::string Game::getAssetsPath() {
    std::string path = argv[0];
    if (path.find("bin") != std::string::npos) {
        return "./" + assetsFolderName + "/";
    }
    return "../" + assetsFolderName + "/";
}

bool Game::isWindowOpen() const {
    return isOpen;
}
sf::Vector2u Game::getWindowSize() const {
    return window->getSize();
}
void Game::update(){
    updatePollEvenets();
    if (started) {
        started = false;
        states.push(new GameState(window, getAssetsPath()));
    }
    if(states.size()>0) {
        if (!states.top()->getState()) {
            states.pop();
        } else {
            states.top()->update(dt);
        }
    }
}
void Game::render(){
    window->clear();

    if (states.size() > 0) {
        states.top()->render(window);
    } else {
        isOpen = false;
        window->close();
    }
    window->display();
}
