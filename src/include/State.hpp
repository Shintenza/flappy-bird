#pragma once
#include "utils/logging.hpp"
#include "DbHandler.hpp"

#include <SFML/Graphics.hpp>

class State {
private:
    sf::RenderWindow* window;
    bool isActive;
    std::map<std::string, sf::Texture*> textures;
    std::string stateName;
protected:
    DbHandler *dbHandler;
public: 
    State(sf::RenderWindow* window, DbHandler* dbHandler, std::string state_name);
    ~State();

    void endState();
    bool getState();
    void loadTexture(std::string texture_name, std::string path);
    sf::RenderWindow* getWindow();
    sf::Texture* getTexture(std::string texture_name);
    virtual void handleInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target) = 0;
};
