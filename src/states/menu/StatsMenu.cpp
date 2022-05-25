#include "../../include/StatsMenu.hpp"

StatsMenu::StatsMenu(std::string& assetsPath, sf::Vector2u windowSize, std::vector<bestScores> given_scores, bool& isStatScreenActive, sf::Vector2f& _mousePos) : 
    mousePos(_mousePos),
    active(isStatScreenActive) {
    scores = given_scores;
    init(assetsPath, windowSize);
}

StatsMenu::~StatsMenu() {
    delete goBack;
}
void StatsMenu::loadFonts(std::string& assetsFolderPath) {
    if (!font.loadFromFile(assetsFolderPath+"font2.ttf")) {
        log(2, "failed to load main font");
        exit(1); }
}
void StatsMenu::positionMenu( std::string& assetsPath, sf::Vector2u windowSize) {
    float b_height = windowSize.y*0.1f;
    float b_width = windowSize.x*0.3f;

    sf::Vector2f buttonSize =sf::Vector2f(b_width, b_height);
    sf::Vector2f buttonPos = sf::Vector2f(windowSize.x *.5f - buttonSize.x*.5f, windowSize.y - 100);
    
    goBack = new Button(mousePos, buttonSize, buttonPos, assetsPath, sf::Color::Cyan, "Back", 37, false);

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
bool StatsMenu::isActive() {
    return active;
}
void StatsMenu::handleInput(sf::Vector2f mousePosView)  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(!isHeld) {
            isHeld = true;
            if (*goBack && active) {
                active = false;
            }
        }
    } else {
        isHeld = false;
    }
}
void StatsMenu::init(std::string& assetsPath, sf::Vector2u windowSize) {
    active = false;
    loadFonts(assetsPath);
    positionMenu(assetsPath, windowSize);
}
void StatsMenu::draw(sf::RenderTarget* window) {
    window->draw(header);
    window->draw(bestScoresHeader);
    window->draw(bestScoresText);
    goBack->draw(window);
}
