#include <iostream>
#include "include/Game.hpp"

int main(int argc, char** argv) {
    Game game(argc, argv);

    while(game.isWindowOpen()){
        game.updateDt();
        game.update();
        game.render();
    }
    return 0;
}
