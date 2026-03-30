#pragma once

#include "raylib.h"
#include "hitbox.h"

#include <memory>

class Penguin {

private:
    int id;
    Vector2 velocity = {0, 0};
    Vector2 pos = (Vector2) {640, 360};
    Hitbox hitbox = Hitbox(std::make_unique<H_Rectangle>(pos.x, pos.y, 20, 40));

    void handleInput();

public:
    Penguin();
    void update();
    void draw();

};