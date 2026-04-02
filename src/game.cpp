#include "game.h"
#include "raylib.h"
#include "penguin.h"
#include "objects.h"
#include "platform.h"
#include "assetManager.h"

void Game::update()
{
    world.update();
}

void Game::draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawFPS(10, 10);

    world.draw();

    EndDrawing();
}

Game::Game()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Penguin Game");
    SetTargetFPS(60);
    AssetManager::loadAssets();
    world.addObject(std::move(std::make_unique<Penguin>()));
    world.addObject(std::move(std::make_unique<Platform>(Hitbox(std::make_unique<H_Rectangle>(0, 600, 1280, 20)), 0, 600, 1280, 20, BLUE)));
    world.addObject(std::move(std::make_unique<Platform>(Hitbox(std::make_unique<H_Rectangle>(0, 525, 1280, 20)), 0, 525, 1280, 20, BLUE)));
    world.addObject(std::move(std::make_unique<Platform>(Hitbox(std::make_unique<H_Rectangle>(100, 0, 20, 720)), 100, 0, 20, 720, BLUE)));
    world.addObject(std::move(std::make_unique<Platform>(Hitbox(std::make_unique<H_Rectangle>(1100, 0, 20, 720)), 1100, 0, 20, 720, BLUE)));
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
    AssetManager::unloadAssets();
    CloseWindow();
}