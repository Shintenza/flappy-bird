#pragma once

#include <SFML/Graphics.hpp>

class State {
private:
    sf::RenderWindow* window;
    bool quit;
    bool paused;
    std::map<std::string, sf::Texture*> textures;
public: 
    State(sf::RenderWindow* window);
    ~State();

    void endState();
    void pauseState();
    void resumeState();
    void loadTexture(std::string texture_name, std::string path);
    sf::RenderWindow* getWindow();
    sf::Texture* getTexture(std::string texture_name);
    virtual void handleInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target) = 0;
};
