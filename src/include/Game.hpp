#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <stack>

#include "State.hpp"

class Game {
private:
    sf::VideoMode windowMode;
    sf::RenderWindow* window;
    sf::Event event;
    
    std::stack<State*> states;

    sf::Clock dtClock;
    float dt;

    bool isOpen;

    void initState();
    void initVariables();
    void initWindow();
public:
    Game();
    ~Game();
    void updateDt();
    void updatePollEvenets();
    void inputUpdate();

    bool isWindowOpen() const;
    sf::Vector2u getWindowSize() const;
    void update();
    void render();
};

