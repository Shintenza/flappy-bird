#include "include/GameState.hpp"
#include <iostream>

// TODO write better path handler
#define FONT_PATH "./assets/font1.ttf"
#define BACKGROUND_PATH "./assets/background.png"

void GameState::loadFonts() {
    if (!font.loadFromFile(FONT_PATH)) {
        std::cout<<"Failed to load font1"<<std::endl;
        exit(1);
    }
    text.setFont(font);
}

void GameState::loadBackground() {
    if(!backgroundTexture.loadFromFile(BACKGROUND_PATH)) {
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

sf::Text GameState::getStartText() {
    text.setCharacterSize(69);
    text.setString("Tap space to start playing");

    unsigned yPos = 0.25 * getWindow()->getSize().y;
    unsigned xPos = 0.5  * getWindow()->getSize().x - (text.getGlobalBounds().width / 2);

    text.setPosition(xPos, yPos);

    return text;
}
sf::Text GameState::getEndingText() {
    text.setCharacterSize(69);
    text.setString("Game Over");

    unsigned yPos = 0.5  * getWindow()->getSize().y - (text.getGlobalBounds().height /2);
    unsigned xPos = 0.5  * getWindow()->getSize().x - (text.getGlobalBounds().width / 2);

    text.setPosition(xPos, yPos);

    return text;
}
GameState::GameState(sf::RenderWindow* window) : State(window) {
    loadTexture("PLAYER", "./assets/bird.png");
    sf::Texture *texture = getTexture("PLAYER");
    if (!texture) {
        std::cout<<"Player texture not found"<<std::endl;
    }
    player = new Player(texture, getWindow()->getSize());
    entities.push_back(player);
    loadFonts();
    loadBackground();
    initCollisionBox();
    isHeld = false;
    gameEnded = false;
    sentStartingMessage = false;
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
        if (!player->checkIfActive() && !sentStartingMessage) {
            sentStartingMessage = true;
            player->startFalling();
        } else {
            if (!isHeld) {
                isHeld = true;
                player->flap(dt);
            }
        }
    } else {
        isHeld = false;
    }
}

void GameState::update(const float& dt) {
    moveBackground();
    handleInput(dt);

    for (int i = 0; i < entities.size(); i++) {
        if (entities.at(i)->checkIfDead(collision_box)) {
            gameEnded = true;
            entities.erase(entities.begin()+i);
            delete entities[i];
        } else {
            entities.at(i)->update(dt);
        }
    }
}

void GameState::render(sf::RenderTarget* window) {
    window->draw(backgroundSprite[0]);
    window->draw(backgroundSprite[1]);

    if (!sentStartingMessage) {
        window->draw(getStartText());
    }
    if (gameEnded) {
        window->draw(getEndingText());
    }

    if (entities.size() > 0) {
        for (Entity *e : entities) {
            e->render(window);
        }
    }
}
