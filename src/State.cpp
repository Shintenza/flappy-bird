#include "include/State.hpp"
#include <iostream>

State::State(sf::RenderWindow* _window) {
   window = _window;
}
void State::loadTexture(std::string name, std::string _path) {
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(_path);
    textures.insert(std::pair<std::string, sf::Texture*>(name, texture));
}
State::~State() {
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
    if (textures.find(name)!=textures.end()) {
        return textures.find(name)->second;
    }
    return NULL;
}
