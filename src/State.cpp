#include "include/State.hpp"
#include <iostream>

State::State(sf::RenderWindow* _window) {
   window = _window;
   isActive = true;
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
    try {
        if (textures.find(name)==textures.end()) {
            throw -1;
        } else {
            return textures.find(name)->second;
        }
    } catch (...) {
        std::cout<<"[ERROR] >> " << "tried to load texture: "<< name << " but it doesn't exist" <<std::endl;
        exit(1);
    }
}
void State::endState() {
    isActive = false;
    std::cout<<"state finished"<<std::endl;
}
bool State::getState() {
   return isActive ;
}
