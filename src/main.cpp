#include <iostream>
#include "include/Game.hpp"

int main() {
    Game game;
    while(game.isWindowOpen()){
        game.update();
        game.render();
    }
    return 0;
}
