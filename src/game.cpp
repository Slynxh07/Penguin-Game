#include "game.h"
#include "raylib.h"
#include "penguin.h"

void Game::update()
{
    player.update();
}

void Game::draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawFPS(10, 10);

    player.draw();

    EndDrawing();
}

Game::Game()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Penguin Game");
    SetTargetFPS(60);
}

bool Game::isRunning()
{
    return running;
}

void Game::run()
{
    if (WindowShouldClose()) running = false;
    update();
    draw();    
}

void Game::close()
{
    CloseWindow();

}