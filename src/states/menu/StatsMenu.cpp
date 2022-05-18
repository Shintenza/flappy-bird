#include "../../include/StatsMenu.hpp"

void StatsScreen::loadFonts(std::string& assetsFolderPath) {
    if (!font.loadFromFile(assetsFolderPath+"font2.ttf")) {
        log(2, "failed to load main font");
        exit(1); }
}
void StatsScreen::positionMenu(sf::Vector2u windowSize) {
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
StatsScreen::StatsScreen(std::vector<bestScores> given_scores, bool& isStatScreenActive) : active(isStatScreenActive) {
    scores = given_scores;
}
bool StatsScreen::isActive() {
    return active;
}
void StatsScreen::handleInput(sf::Vector2f mousePosView)  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(!isHeld) {
            isHeld = true;
            if (goBackButton.getGlobalBounds().contains(mousePosView) && active) {
                active = false;
            }
        }
    } else {
        isHeld = false;
    }
}
void StatsScreen::init(std::string& assetsFolderPath, sf::Vector2u windowSize) {
    active = false;
    loadFonts(assetsFolderPath);
    positionMenu(windowSize);
}
void StatsScreen::draw(sf::RenderTarget* window) {
    window->draw(header);
    window->draw(bestScoresHeader);
    window->draw(bestScoresText);
    window->draw(goBackButton);
    window->draw(buttonText);
}
