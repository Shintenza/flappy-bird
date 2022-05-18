#include "include/MenuState.hpp" 
#include "include/DbHandler.hpp"
#include <ctime>
#include <time.h>
#include <iostream>

MenuState::MenuState(sf::RenderWindow* _window, DbHandler* dbh, std::string assets_path, bool& started) : State(_window, dbh, "MenuState"), isGameStarted(started){
    init(assets_path);
}
void MenuState::updateMousePos() {
   mousePos = sf::Mouse::getPosition(*getWindow());
   mousePosView = getWindow()->mapPixelToCoords(mousePos);
}
void MenuState::init(std::string assetsFolderPath) {

    loadTexture("BACKGROUND", assetsFolderPath+"background.png");
    if (!getTexture("BACKGROUND")) {
        std::cout<<"Failed to load bg image"<<std::endl;
        exit(1);
    }
    backgroundSprite.setTexture(*getTexture("BACKGROUND"));

    main.loadFonts(assetsFolderPath);
    main.positionMenu(getWindow()->getSize());
    stats.loadFonts(assetsFolderPath);
    stats.positionMenu(getWindow()->getSize(), dbHandler->getBestScores());
    isHeld = false;
    isStatScreenActive = false;
    
}
void MenuState::handleInput(const float& dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        endState();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(!isHeld) {
            isHeld = true;
            if (main.quitGameButton.getGlobalBounds().contains(mousePosView) && !isStatScreenActive) {
                endState();
            }
            if (main.startGameButton.getGlobalBounds().contains(mousePosView) && !isStatScreenActive) {
                isGameStarted = true;
            }
            if (main.checkStatsButton.getGlobalBounds().contains(mousePosView) && !isStatScreenActive) {
                isStatScreenActive = true;
            }
            if (stats.goBackButton.getGlobalBounds().contains(mousePosView) && isStatScreenActive) {
                isStatScreenActive = false;
            }
        }
    } else {
        isHeld = false;
    }
}
void MenuState::update(const float& dt) {
    updateMousePos();
    handleInput(dt);
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
void MainMenu::loadFonts(std::string& assetsFolderPath) {
    if (!font.loadFromFile(assetsFolderPath+"font1.ttf")) {
        log(2, "failed to load main font");
        exit(1);
    }
}
void MainMenu::positionMenu(sf::Vector2u windowSize) {
    sf::Vector2f menuBoxPosition;
    float height = windowSize.y*0.7f;
    float width = windowSize.x*0.7f;


    menuBox.setSize(sf::Vector2f(width, height));
    menuBox.setPosition(windowSize.x *.5f - width *.5f, windowSize.y * .5f - height *.5f);
    menuBox.setFillColor(sf::Color::Yellow);
    menuBoxPosition = menuBox.getPosition();
    
    gameTitle.setFont(font);
    gameTitle.setString("Flappy Bird");
    gameTitle.setCharacterSize(width*0.14f);
    gameTitle.setPosition(windowSize.x *.5f - gameTitle.getGlobalBounds().width * .5f, menuBoxPosition.y + 10);
    gameTitle.setOutlineThickness(2);
    gameTitle.setOutlineColor(sf::Color::Black);

    startGameButton.setSize(sf::Vector2f(width*.5f, height*.15f));
    startGameButton.setFillColor(sf::Color::Blue);
    startGameButton.setPosition(windowSize.x * 0.5f - startGameButton.getGlobalBounds().width * 0.5f, 
    gameTitle.getPosition().y + gameTitle.getGlobalBounds().height + 60);

    quitGameButton.setSize(sf::Vector2f(width*.5f, height*.15f));
    quitGameButton.setFillColor(sf::Color::Red);
    quitGameButton.setPosition(windowSize.x * 0.5f - quitGameButton.getGlobalBounds().width * 0.5f , startGameButton.getPosition().y + startGameButton.getSize().y + 40);

    startGameText.setString("Start");
    startGameText.setCharacterSize(width*0.09f);
    startGameText.setOutlineColor(sf::Color::Black);
    startGameText.setOutlineThickness(2);
    startGameText.setFont(font);

    quitGameText.setString("Quit");
    quitGameText.setCharacterSize(width*0.09f);
    quitGameText.setOutlineColor(sf::Color::Black);
    quitGameText.setOutlineThickness(2);
    quitGameText.setFont(font);

    startGameText.setPosition(windowSize.x *.5f - startGameText.getGlobalBounds().width *.5f, 
    startGameButton.getPosition().y + startGameButton.getSize().y *.5f - startGameText.getGlobalBounds().height);
    
    quitGameText.setPosition(windowSize.x *.5f - quitGameText.getGlobalBounds().width *.5f, 
        quitGameButton.getPosition().y + quitGameButton.getSize().y *.5f - quitGameText.getGlobalBounds().height);

    checkStatsButton.setSize(sf::Vector2f(width*.5f, height*.15f));
    checkStatsButton.setFillColor(sf::Color::Cyan);
    checkStatsButton.setPosition(windowSize.x * 0.5f - checkStatsButton.getGlobalBounds().width * 0.5f , quitGameButton.getPosition().y + quitGameButton.getSize().y + 40);

    checkStatsText.setFont(font);
    checkStatsText.setString("Stats");
    checkStatsText.setOutlineColor(sf::Color::Black);
    checkStatsText.setOutlineThickness(2);
    checkStatsText.setCharacterSize(width*0.09f);

    checkStatsText.setPosition(windowSize.x *.5f - checkStatsText.getGlobalBounds().width *.5f, 
        checkStatsButton.getPosition().y + checkStatsButton.getSize().y *.5f - checkStatsText.getGlobalBounds().height);

}

void MainMenu::draw(sf::RenderTarget* window) {
    window->draw(menuBox);
    window->draw(gameTitle);
    window->draw(startGameButton);
    window->draw(quitGameButton);
    window->draw(startGameText);
    window->draw(quitGameText);
    window->draw(checkStatsButton);
    window->draw(checkStatsText);
}

// StatsScreen

void StatsScreen::loadFonts(std::string& assetsFolderPath) {
    if (!font.loadFromFile(assetsFolderPath+"font2.ttf")) {
        log(2, "failed to load main font");
        exit(1);
    }
}
void StatsScreen::positionMenu(sf::Vector2u windowSize, std::vector<bestScores> scores) {
    float b_height = windowSize.y*0.1f;
    float b_width = windowSize.x*0.3f;

    buttonText.setFont(font);
    buttonText.setString("Back");
    goBackButton.setSize(sf::Vector2f(b_width, b_height));
    goBackButton.setPosition(windowSize.x *.5f - goBackButton.getGlobalBounds().width*.5f, windowSize.y - 100);
    goBackButton.setFillColor(sf::Color::Blue);

    buttonText.setPosition(windowSize.x *.5f - buttonText.getGlobalBounds().width *.5f, 
            goBackButton.getPosition().y + goBackButton.getGlobalBounds().height *0.5f - buttonText.getGlobalBounds().height*0.5f);
            
    header.setFont(font);
    header.setString("Game stats");
    header.setCharacterSize(37);
    header.setPosition(windowSize.x*.5f - header.getGlobalBounds().width*.5f, .15f*windowSize.y);

    bestScoresHeader.setFont(font);
    bestScoresHeader.setString("Top sessions:");
    bestScoresHeader.setCharacterSize(28);
    bestScoresHeader.setPosition(windowSize.x*.5f - bestScoresHeader.getGlobalBounds().width*.5f, header.getPosition().y + header.getGlobalBounds().height + 30);
    
    bestScoresText.setFont(font);
    bestScoresText.setCharacterSize(19);
    std::string statsString = "";

    if (scores.empty()) {
        statsString = "Nothing to display";
    } else {
        for (auto score : scores) {
            std::time_t time = score.time;
            struct std::tm* tm = std::localtime(&time);
            char date[20];
            std::strftime(date, sizeof(date), "%d-%m-%Y", tm);
            statsString+= "Date: " + std::string(date) + " Score: " + std::to_string(score.score) + " Tries: " + std::to_string(score.number_of_tries) + "\n";
        }
    }
    bestScoresText.setString(statsString);
    bestScoresText.setPosition(windowSize.x*.5f - bestScoresText.getGlobalBounds().width*.5f, bestScoresHeader.getPosition().y + bestScoresHeader.getGlobalBounds().height + 30);
     
}
void StatsScreen::draw(sf::RenderTarget* window) {
    window->draw(header);
    window->draw(bestScoresHeader);
    window->draw(bestScoresText);
    window->draw(goBackButton);
    window->draw(buttonText);
}
