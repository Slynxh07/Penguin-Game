#pragma once

#include "raylib.h"
#include "objects.h"

#include <memory>

class Penguin : public Object {

private:
    int id;
    Vector2 velocity = {0, 0};
    bool grounded;

    void handleInput();

public:
    Penguin();
    void update() override;
    void draw() override;
    void handleCollision(const Object& other) override;
};