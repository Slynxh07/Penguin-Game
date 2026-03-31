#pragma once

#include "raylib.h"
#include "objects.h"
#include "animation.h"
#include "animationPlayer.h"
#include "assetManager.h"

#include <memory>
#include <vector>

class Penguin : public Object {

private:
    int id;
    Vector2 velocity = {0, 0};
    bool grounded;
    bool flip;
    AnimationPlayer animationPlayer;
    Animation penguinIdleAnim = Animation(AssetManager::penguinIdle, 8, {{0, 0, 16, 16}, {16, 0, 16, 16}, {32, 0, 16, 16}, {48, 0, 16, 16}}, 4, 0);

    void handleInput();

public:
    Penguin();
    void update() override;
    void draw() override;
    void handleCollision(const Object& other) override;
};