#pragma once

#include "objects.h"

class Platform : public Object {

private:
    Rectangle rect;
    Color color;

public:
    Platform(Hitbox hitbox, float x, float y, float width, float height, Color color) : Object(std::move(hitbox)), rect{ x, y, width, height }, color(color) {
        pos = {x, y};
    }

    void update() override;
    void draw() override;
    void handleCollision(const Object& other) override;
};