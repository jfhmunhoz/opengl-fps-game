#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController
{
public:
    GameController();
    void init();
    void update(float deltaTime);
    void handleInput();
    void shutdown();
    
private:
    // Game state management
};

#endif
