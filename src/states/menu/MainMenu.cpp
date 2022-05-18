#include "../../include/MainMenu.hpp"
#include "../../include/utils/logging.hpp"

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

void MainMenu::handleInput(sf::Vector2f mousePosView, bool& isStatScreenActive, bool& isGameStarted) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(!isHeld) {
            isHeld = true;
            if (quitGameButton.getGlobalBounds().contains(mousePosView) && !isStatScreenActive) {
                quit = true;
            }
            if (startGameButton.getGlobalBounds().contains(mousePosView) && !isStatScreenActive) {
                isGameStarted = true;
            }
            if (checkStatsButton.getGlobalBounds().contains(mousePosView) && !isStatScreenActive) {
                isStatScreenActive = true;
            }
        }
    } else {
        isHeld = false;
    }
}
bool MainMenu::getQuit() {
    return quit;
}
void MainMenu::init(std::string& assetsFolderPath, sf::Vector2u windowSize) {
    loadFonts(assetsFolderPath);
    positionMenu(windowSize);
    quit = false;
    isHeld = false;
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
