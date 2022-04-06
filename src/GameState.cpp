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
void GameState::moveBackground(const float& dt) {
    int bgTextureSize = backgroundTexture.getSize().x;
    
    if (std::abs(backgroundSprite[0].getPosition().x) > bgTextureSize) {
        backgroundSprite[0].setPosition(backgroundSprite[1].getPosition().x + bgTextureSize, -backgroundYOffset );
    }

    if (std::abs(backgroundSprite[1].getPosition().x) > bgTextureSize) {
        backgroundSprite[1].setPosition(backgroundSprite[0].getPosition().x + bgTextureSize, -backgroundYOffset );
    }

    backgroundSprite[0].move(-backgroundMoveSpeed*dt, 0);
    backgroundSprite[1].move(-backgroundMoveSpeed*dt, 0);
}
void GameState::initCollisionBox() {
    collision_box.setSize(sf::Vector2f(getWindow()->getSize().x, groundHeight));
    collision_box.setPosition(0, getWindow()->getSize().y - groundHeight);
}

void GameState::spawnObstacles() {
    Obstacle *new_obstacle = new Obstacle(getTexture("OBSTACLE"), getWindow()->getSize(), groundHeight, backgroundMoveSpeed);

    if (entities.empty() && gameClock.getElapsedTime().asSeconds() > 4 && !gameEnded && sentStartingMessage) {
        readyToSpawnObstacle = true;
    } else if (entities.size() > 0 && distance < getWindow()->getSize().x - entities.back()->getPosition().x && !gameEnded) {
        readyToSpawnObstacle = true;
    }
    if (readyToSpawnObstacle) {
        entities.push_back(new_obstacle);
        readyToSpawnObstacle = false;
    }
}

void GameState::setScore() {
    if (!entities.empty() 
        && player->getSprite().getPosition().x > (entities.front()->getPosition().x + entities.front()->getBounding().width ) 
        && !entities.front()->checkIfPassed()) {
            score+=1;         
            entities.front()->pass();
    }
}

sf::Text GameState::getStartText() {
    text.setCharacterSize(40);
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
sf::Text GameState::getScoreText() {
    text.setCharacterSize(69);
    text.setString(std::to_string(score));

    unsigned yPos = 0.2  * getWindow()->getSize().y - (text.getGlobalBounds().height /2);
    unsigned xPos = 0.5  * getWindow()->getSize().x - (text.getGlobalBounds().width / 2);

    text.setPosition(xPos, yPos);
    return text;
}
GameState::GameState(sf::RenderWindow* window) : State(window) {
    loadTexture("PLAYER", "./assets/bird.png");

    sf::Texture *player_texture = getTexture("PLAYER");

    player = new Player(player_texture, getWindow()->getSize());
    loadTexture("OBSTACLE", "./assets/column.png");
    sf::Texture *obstacle_texture = getTexture("OBSTACLE");

    if (!player_texture || !obstacle_texture) {
        std::cout<<"Player or obstacle texture not found"<<std::endl;
    }

    isHeld = false;
    gameEnded = false;
    sentStartingMessage = false;
    readyToSpawnObstacle = false;
    groundHeight = 75;
    backgroundMoveSpeed = 300.f;
    distance = 300.f;
    score = 0;


    loadFonts();
    loadBackground();
    initCollisionBox();
};

void GameState::handleInput(const float& dt) {  
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        std::cout<<"Game state finished"<<std::endl;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if (!player->checkIfActive() && !sentStartingMessage) {
            sentStartingMessage = true;
            player->startFalling();
            gameClock.restart();
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
    moveBackground(dt);
    handleInput(dt);

    if (player->checkIfDead(collision_box)) {
        gameEnded = true;
    } else {
        player->update(dt);
    }
    for (unsigned i = 0; i <entities.size(); i++) {
        if (entities.at(0)->checkIfDead(collision_box)) {
            delete entities[0];
            entities.erase(entities.begin());
        } else {
            entities.at(i)->update(dt);
        }
    }
    spawnObstacles();

    if (entities.size()>0) {
        if (entities.at(0)->isColliding(player->getHitboxBounding())){
            player->stopFalling();
        }
    }
    setScore();
}

void GameState::render(sf::RenderTarget* window) {
    window->draw(backgroundSprite[0]);
    window->draw(backgroundSprite[1]);

    if (!sentStartingMessage) {
        window->draw(getStartText());
    }
    if (sentStartingMessage) {
        window->draw(getScoreText());
    }
    if (entities.size() > 0 ) {
        for (Entity *e : entities) {
            e->render(window);
        }
    }
    if (gameEnded) {
        window->draw(getEndingText());
    } else {
        player->render(window);
    }

}
