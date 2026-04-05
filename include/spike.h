#pragma once

#include "objects.h"
#include "raylib.h"

#include <array>

class Spike : public Object
{

private:
    std::array<Vector2, 3> verticies;
    Color color;

public:
    Spike(Hitbox hitbox, Vector2 v1, Vector2 v2, Vector2 v3, Color color) : Object(std::move(hitbox)), verticies({v1, v2, v3}), color(color) {}

    void update() override;
    void draw() override;
    void handleCollision(const Object& other) override;
    void updatePos() override;
    Vector2 getDimensions() const override;
};