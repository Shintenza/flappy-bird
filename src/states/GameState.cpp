#include "../include/GameState.hpp"
#include "../include/utils/logging.hpp"
#include <iostream>

#define PLAYER_TEXTURE_NAME "bird"
#define OBSTACLE_TEXTURE_NAME "column"

GameState::GameState(sf::RenderWindow* window, DbHandler *dbh, std::string assetsFolderPath, int& sessionStarted)
    : State(window, dbh, "GameState"), started(sessionStarted)
{
    loadTexture(PLAYER_TEXTURE_NAME, assetsFolderPath+PLAYER_TEXTURE_NAME".png");
    loadTexture(OBSTACLE_TEXTURE_NAME, assetsFolderPath+OBSTACLE_TEXTURE_NAME".png");

    sf::Texture *player_texture = getTexture(PLAYER_TEXTURE_NAME);
    sf::Texture *obstacle_texture = getTexture(OBSTACLE_TEXTURE_NAME);

    if (!player_texture || !obstacle_texture) {
        exit(1);
        std::cout<<"Player or obstacle texture not found"<<std::endl;
    }

    player = new Player(player_texture, getWindow()->getSize(), flapCount);

    initVars();
    loadFonts(assetsFolderPath);
    loadBackground(assetsFolderPath);
    initCollisionBox();
};

GameState::~GameState() {
    dbHandler->addSession(started, sessionHighestScore, numberOfTries, flapCount, obstacleCount, dbHandler->checkIfSessionsExists(started));
}

void GameState::initVars() {
    isHeld = false;
    gameEnded = false;
    sentStartingMessage = false;;
    readyToSpawnObstacle = false;
    groundHeight = 75;
    backgroundMoveSpeed = 300.f;
    distance = 300.f;
    
    globalHighestScore = dbHandler->getDbHighestScore();
    sessionHighestScore = 0;
    score = 0;
    numberOfTries = 1;
    flapCount = 0;
    obstacleCount = 0;
}

void GameState::loadFonts(std::string assetsFolderPath) {
    if (!font.loadFromFile(assetsFolderPath+"font1.ttf")) {
        log(2, "failed to load font1");
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

    if (entities.empty() && gameClock.getElapsedTime().asSeconds() > 4 && !gameEnded && sentStartingMessage) {
        readyToSpawnObstacle = true;
    } else if (entities.size() > 0 && distance < getWindow()->getSize().x - entities.back()->getPosition().x && !gameEnded) {
        readyToSpawnObstacle = true;
    }
    if (readyToSpawnObstacle) {
        Obstacle *new_obstacle = new Obstacle(getTexture(OBSTACLE_TEXTURE_NAME), getWindow()->getSize(), groundHeight, backgroundMoveSpeed);
        entities.push_back(new_obstacle);
        readyToSpawnObstacle = false;
    }
}

void GameState::setScore() {
    if (!entities.empty() 
        && player->getSprite().getPosition().x > (entities.front()->getPosition().x + entities.front()->getBounding().width ) 
        && !entities.front()->checkIfPassed()) {
            score++;         
            obstacleCount++;
            entities.front()->pass();
    }
}
void GameState::restartGame() {
    log(0, "Game restarted");
    gameEnded = false;
    sentStartingMessage = false;
    score = 0;
    player->restartPlayer();
    gameClock.restart();
    entities.clear();
    numberOfTries++;
}
void GameState::updateLastScores(unsigned& score){
    std::vector<unsigned>::iterator min = std::min_element(lastSessionScores.begin(), lastSessionScores.end());
    unsigned min_index = std::distance(lastSessionScores.begin(), min);

    if (lastSessionScores.size() < 5 && std::find(lastSessionScores.begin(), lastSessionScores.end(), score) == lastSessionScores.end() && score > 0 ) {
        lastSessionScores.push_back(score);
    } else if (lastSessionScores.size() >= 5 && std::find(lastSessionScores.begin(), lastSessionScores.end(), score) == lastSessionScores.end() && score > lastSessionScores[min_index] && score > 0) {
        lastSessionScores.at(min_index) = score;
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
sf::Text GameState::getBestScore () {
    unsigned yPos = text.getPosition().y + text.getGlobalBounds().height +20;
    unsigned xPos;

    s_text.setFont(font);
    s_text.setCharacterSize(21);
    xPos = 0.5f * getWindow()->getSize().x - (s_text.getGlobalBounds().width / 2);
    s_text.setString("Global highest score: " + std::to_string(globalHighestScore));
    s_text.setPosition(xPos, yPos);

    return s_text;
}
sf::Text GameState::getBestSessionScores() {
    unsigned yPos = s_text.getPosition().y + s_text.getGlobalBounds().height + 32;
    unsigned xPos;
    std::string returnStr = "Best scores of this session:";
    
    std::sort(lastSessionScores.begin(), lastSessionScores.end());

    best_scores.setFont(font);
    s_text.setCharacterSize(21);
    xPos = 0.5f * getWindow()->getSize().x - (best_scores.getGlobalBounds().width / 2);

    if (lastSessionScores.size() > 0) {
        for(std::vector<unsigned>::reverse_iterator it = lastSessionScores.rbegin(); it != lastSessionScores.rend(); ++it) {
            if(it == (--lastSessionScores.rend())) {
                returnStr+=" "+ std::to_string(*it);
            } else {
                returnStr+=" " + std::to_string(*it)+',';
            }
        }
    }
    best_scores.setString(returnStr);
    best_scores.setPosition(xPos, yPos);

    return best_scores; 
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
        updateLastScores(score);

        if (score > sessionHighestScore) 
            sessionHighestScore = score;

        if (sessionHighestScore > globalHighestScore)
            globalHighestScore = sessionHighestScore;

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
        window->draw(getBestScore());
        window->draw(getBestSessionScores());
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
