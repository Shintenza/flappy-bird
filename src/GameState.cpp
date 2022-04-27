#include "include/GameState.hpp"
#include <iostream>

void GameState::loadFonts(std::string assetsFolderPath) {
    if (!font.loadFromFile(assetsFolderPath+"font1.ttf")) {
        std::cout<<"Failed to load font1"<<std::endl;
        exit(1);
    }
    text.setFont(font);
}

void GameState::loadBackground(std::string assetsFolderPath) {
    if(!backgroundTexture.loadFromFile(assetsFolderPath+"background.png")) {
        std::cout<<"Failed to load background texture"<<std::endl;
        exit(1);
    }
    if (!groundTexture.loadFromFile(assetsFolderPath+"ground.png")) {
        std::cout<<"Failed to load background texture"<<std::endl;
        exit(1);
    }
    backgroundYOffset = backgroundTexture.getSize().y - getWindow()->getSize().y;
    for (int i = 0; i < 2; i++) {
        background.backgroundSprite[i].setTexture(backgroundTexture);
        background.groundSprite[i].setTexture(groundTexture);

    }
    background.backgroundSprite[0].setPosition(0, -backgroundYOffset - groundHeight);
    background.backgroundSprite[1].setPosition(backgroundTexture.getSize().x, -backgroundYOffset - groundHeight);
    background.groundSprite[0].setPosition(0, getWindow()->getSize().y - groundHeight);
    background.groundSprite[1].setPosition(groundTexture.getSize().x, getWindow()->getSize().y - groundHeight);
}
void GameState::moveBackground(const float& dt) {
    int bgTextureSize = backgroundTexture.getSize().x;
    int grTextureSize = groundTexture.getSize().x;
    
    if (std::abs(background.backgroundSprite[0].getPosition().x) > bgTextureSize) {
        background.backgroundSprite[0].setPosition(background.backgroundSprite[1].getPosition().x + bgTextureSize, -backgroundYOffset - groundHeight);
    }
    if (std::abs(background.groundSprite[0].getPosition().x) > grTextureSize) {
        background.groundSprite[0].setPosition(background.groundSprite[1].getPosition().x + grTextureSize, getWindow()->getSize().y - groundHeight );
    }
    if (std::abs(background.backgroundSprite[1].getPosition().x) > bgTextureSize) {
        background.backgroundSprite[1].setPosition(background.backgroundSprite[0].getPosition().x + bgTextureSize, -backgroundYOffset - groundHeight);
    }
    if (std::abs(background.groundSprite[1].getPosition().x) > grTextureSize) {
        background.groundSprite[1].setPosition(background.groundSprite[0].getPosition().x + grTextureSize, getWindow()->getSize().y - groundHeight );
    }


    background.backgroundSprite[0].move(-backgroundMoveSpeed*dt, 0);
    background.backgroundSprite[1].move(-backgroundMoveSpeed*dt, 0);
    background.groundSprite[0].move(-backgroundMoveSpeed*dt, 0);
    background.groundSprite[1].move(-backgroundMoveSpeed*dt, 0);
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
void GameState::restartGame() {
    std::cout<<"Game restarted"<<std::endl;
    gameEnded = false;
    sentStartingMessage = false;
    score = 0;
    player->restartPlayer();
    gameClock.restart();
    entities.clear();
}

sf::Text GameState::getStartText() {
    text.setCharacterSize(40);
    text.setString("Tap space to start playing");

    unsigned yPos = 0.25 * getWindow()->getSize().y;
    unsigned xPos = 0.5  * getWindow()->getSize().x - (text.getGlobalBounds().width / 2);

    text.setPosition(xPos, yPos);

    return text;
}
std::array<sf::Text,2> GameState::getEndingText() {
    text.setCharacterSize(69);
    text.setString("Game Over");
    s_text.setCharacterSize(25);
    s_text.setFont(font);
    s_text.setString("Press space to start again");

    unsigned yPos = 0.5  * getWindow()->getSize().y - (text.getGlobalBounds().height /2);
    unsigned xPos = 0.5  * getWindow()->getSize().x - (text.getGlobalBounds().width / 2);
    unsigned s_xPos = 0.5  * getWindow()->getSize().x - (s_text.getGlobalBounds().width / 2);

    text.setPosition(xPos, yPos);
    s_text.setPosition(s_xPos, yPos + text.getGlobalBounds().height + 40);

    return {text, s_text};
}
sf::Text GameState::getScoreText() {
    text.setCharacterSize(69);
    text.setString(std::to_string(score));

    unsigned yPos = 0.2  * getWindow()->getSize().y - (text.getGlobalBounds().height /2);
    unsigned xPos = 0.5  * getWindow()->getSize().x - (text.getGlobalBounds().width / 2);

    text.setPosition(xPos, yPos);
    return text;
}
GameState::GameState(sf::RenderWindow* window, std::string assetsFolderPath) : State(window) {
    loadTexture("PLAYER", assetsFolderPath+"bird.png");

    sf::Texture *player_texture = getTexture("PLAYER");

    player = new Player(player_texture, getWindow()->getSize());
    loadTexture("OBSTACLE", assetsFolderPath+"column.png");
    sf::Texture *obstacle_texture = getTexture("OBSTACLE");

    if (!player_texture || !obstacle_texture) {
        std::cout<<"Player or obstacle texture not found"<<std::endl;
    }

    isHeld = false;
    gameEnded = false;
    sentStartingMessage = false;;
    readyToSpawnObstacle = false;
    groundHeight = 75;
    backgroundMoveSpeed = 300.f;
    distance = 300.f;
    score = 0;


    loadFonts(assetsFolderPath);
    loadBackground(assetsFolderPath);
    initCollisionBox();
};

void GameState::handleInput(const float& dt) {  
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && gameEnded) {
        endState();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if (!player->checkIfActive() && !sentStartingMessage && !gameEnded && !isHeld) {
            sentStartingMessage = true;
            player->startFalling();
            gameClock.restart();
        } else {
            if (!isHeld) {
                isHeld = true;
                if (gameEnded)
                    restartGame();
                else 
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

    if (player->checkIfDead(collision_box) && sentStartingMessage) {
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
    window->draw(background.backgroundSprite[0]);
    window->draw(background.backgroundSprite[1]);

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
    window->draw(background.groundSprite[0]);
    window->draw(background.groundSprite[1]);
    if (gameEnded) {
        for (sf::Text text : getEndingText()) {
            window->draw(text);
        }
    } else {
        player->render(window);
    }
}
