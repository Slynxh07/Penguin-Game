#pragma once

#include "penguin.h"

class Game {

private:
    bool running = true;
    static constexpr int WINDOW_WIDTH = 1280;
    static constexpr int WINDOW_HEIGHT = 720;
    Penguin player;

    void update();
    void draw();

public:
    Game();
    bool isRunning();
    void run();
    void close();
};