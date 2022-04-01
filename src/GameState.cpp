#include "include/GameState.hpp"
#include <iostream>

void GameState::loadBackground() {
    if(!backgroundTexture.loadFromFile("./assets/background.png")) {
        std::cout<<"Failed to load background texture"<<std::endl;
        exit(1);
    }
    backgroundYOffset = backgroundTexture.getSize().y - getWindow()->getSize().y;

    backgroundSprite[0].setTexture(backgroundTexture);
    backgroundSprite[1].setTexture(backgroundTexture);
    backgroundSprite[0].setPosition(0, -backgroundYOffset);
    backgroundSprite[1].setPosition(backgroundTexture.getSize().x, -backgroundYOffset);
}
void GameState::moveBackground() {
    int bgTextureSize = backgroundTexture.getSize().x;
    
    if (std::abs(backgroundSprite[0].getPosition().x) > bgTextureSize) {
        backgroundSprite[0].setPosition(backgroundSprite[1].getPosition().x + bgTextureSize, -backgroundYOffset );
    }

    if (std::abs(backgroundSprite[1].getPosition().x) > bgTextureSize) {
        backgroundSprite[1].setPosition(backgroundSprite[0].getPosition().x + bgTextureSize, -backgroundYOffset );
    }

    backgroundSprite[0].move(-5.f, 0);
    backgroundSprite[1].move(-5.f, 0);
}
void GameState::initCollisionBox() {
    int offsetY = 75;
    collision_box.setSize(sf::Vector2f(getWindow()->getSize().x, offsetY));
    collision_box.setPosition(0, getWindow()->getSize().y - offsetY);
}

GameState::GameState(sf::RenderWindow* window) : State(window) {
    loadTexture("PLAYER", "./assets/bird.png");
    sf::Texture *texture = getTexture("PLAYER");
    if (!texture) {
        std::cout<<"Player texture not found"<<std::endl;
    }
    player = new Player(texture);
    entities.push_back(player);
    loadBackground();
    initCollisionBox();
    isHeld = false;
};

void GameState::handleInput(const float& dt) {  
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        std::cout<<"Game state finished"<<std::endl;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        player->move( 0, -5);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player->move(-5, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        player->move(0, 5);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player->move(5, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if (!isHeld) {
            isHeld = true;
            player->flap(dt);
        }
    } else {
        isHeld = false;
    }
}

void GameState::update(const float& dt) {
    moveBackground();
    player->update(dt);
    handleInput(dt);

    for (int i = 0; i< entities.size(); i++) {
        if (entities.at(i)->checkIfDead(collision_box)) {
            entities.erase(entities.begin()+i);
        }
    }
}

void GameState::render(sf::RenderTarget* window) {
    window->draw(backgroundSprite[0]);
    window->draw(backgroundSprite[1]);

    if (entities.size() > 0) {
        for (Entity *e : entities) {
            e->render(window);
        }
    }
}
