#include "../../include/MainMenu.hpp"
#include "../../include/utils/logging.hpp"

void p_delete(Button *p) {
    delete p;
}
MainMenu::MainMenu(std::string &assetsFolderPath, sf::Vector2u windowSize, sf::Vector2f& _mousePosView, StatsMenu& _statsMenu) :
    statsMenu(_statsMenu),
    mousePosView(_mousePosView) {
    init(assetsFolderPath, windowSize);
}

MainMenu::~MainMenu() {
    std::for_each(buttons.begin(), buttons.end(), p_delete);
    buttons.clear();
    #if DEV_MODE == 1
    log(0, "MainMenu destructor");
    #endif
}

void MainMenu::loadFonts(std::string& assetsFolderPath) {
    if (!font.loadFromFile(assetsFolderPath+"font1.ttf")) {
        log(2, "failed to load main font");
        exit(1);
    }
}
void MainMenu::positionMenu(sf::Vector2u windowSize, std::string& assetsFolderPath) {
    sf::Vector2f menuBoxPosition;
    float height = windowSize.y*0.7f;
    float width = windowSize.x*0.7f;


    menuBox.setSize(sf::Vector2f(width, height));
    menuBox.setPosition(windowSize.x *.5f - width *.5f, windowSize.y * .5f - height *.5f);
    menuBox.setFillColor(sf::Color(245, 241, 29));
    menuBoxPosition = menuBox.getPosition();
    
    gameTitle.setFont(font);
    gameTitle.setString("Flappy Bird");
    gameTitle.setCharacterSize(width*0.14f);
    gameTitle.setPosition(windowSize.x *.5f - gameTitle.getGlobalBounds().width * .5f, menuBoxPosition.y + 10);
    gameTitle.setOutlineThickness(2);
    gameTitle.setOutlineColor(sf::Color::Black);

    sf::Vector2f buttonSize = sf::Vector2f(width*.5f, height*.15f);
    sf::Vector2f startGamePos = sf::Vector2f(windowSize.x * 0.5f - buttonSize.x * 0.5f, gameTitle.getPosition().y + gameTitle.getGlobalBounds().height + 60);

    buttons.push_back(new Button(mousePosView, buttonSize, startGamePos, assetsFolderPath, sf::Color(18, 255, 26), "Start", width*.09f, true));

    sf::Vector2f quitGamePos = sf::Vector2f(buttons.back()->getEndYPosition().x, buttons.back()->getEndYPosition().y + 40);

    buttons.push_back(new Button(mousePosView, buttonSize, quitGamePos, assetsFolderPath, sf::Color(252, 33, 18), "Quit", width*.09f, true));
    
    sf::Vector2f statsBtnPos = sf::Vector2f(buttons.back()->getEndYPosition().x, buttons.back()->getEndYPosition().y + 40);

    buttons.push_back(new Button(mousePosView, buttonSize, statsBtnPos, assetsFolderPath, sf::Color(30, 118, 250), "Stats", width*.09f, true));

}

void MainMenu::handleInput(sf::Vector2f mousePosView, bool& isStatScreenActive, bool& isGameStarted) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(!isHeld) {
            isHeld = true;
            //TODO just make it better pls
            // Przyk??adowe u??ycie: przeci????anie operator??w
            if (*buttons[1] && !isStatScreenActive) {
                quit = true;
            }
            if (*buttons[0] && !isStatScreenActive) {
                isGameStarted = true;
            }
            if (*buttons[2] && !isStatScreenActive) {
                statsMenu.fetchData();
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
    positionMenu(windowSize, assetsFolderPath);
    quit = false;
    isHeld = false;
}

void MainMenu::draw(sf::RenderTarget* window) {
    window->draw(menuBox);
    window->draw(gameTitle);
    // Przyk??adowe u??ycie: zakresowa p??tla for
    for (Button* btn : buttons) {
        btn->draw(window);
    }
}
