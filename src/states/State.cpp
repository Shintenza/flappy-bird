#include "../include/State.hpp"
#include <iostream>

State::State(sf::RenderWindow* _window, DbHandler* dbH, std::string state_name) {
    window = _window;
    isActive = true;
    stateName = state_name;
    dbHandler = dbH;
}
void State::loadTexture(std::string name, std::string _path) {
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(_path);
    textures.insert(std::pair<std::string, sf::Texture*>(name, texture));
}
State::~State() {
    // Przykładowe użycie: iteratory
    std::map<std::string, sf::Texture*>::iterator iter;
    for (iter = textures.begin(); iter!= textures.end();iter++) {
        delete iter->second;
    }
    textures.clear();
}
sf::RenderWindow* State::getWindow() {
    return window;
}
sf::Texture* State::getTexture(std::string name) {
    // Przykładowe użycie: wyjątki
    try {
        if (textures.find(name)==textures.end()) {
            throw -1;
        } else {
            return textures.find(name)->second;
        }
    } catch (...) {
        log<std::string>(2, "tried to load texture: " + name + " but it doesn't exist!!!");
        exit(1);
    }
}
void State::endState() {
    isActive = false;
    #if DEV_MODE == 1
    log<std::string>(0, "state: " + stateName + " finished!");
    #endif
}
bool State::getState() {
   return isActive ;
}
