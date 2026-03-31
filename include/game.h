#pragma once

#include "penguin.h"
#include "world.h"

class Game {

private:
    bool running = true;
    static constexpr int WINDOW_WIDTH = 1280;
    static constexpr int WINDOW_HEIGHT = 720;
    
    World world;
    Penguin player;

    void update();
    void draw();

public:
    Game();
    bool isRunning();
    void run();
    void close();
};