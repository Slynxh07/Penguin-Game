#pragma once

#include "raylib.h"
#include "objects.h"
#include "animation.h"
#include "animationPlayer.h"
#include "assetManager.h"

#include <memory>
#include <vector>

typedef enum PlayerState {
    IDLE,
    RUNNING,
    JUMPING,
    FALLING,
    DEAD
} PlayerState;

class Penguin : public Object {

private:
    int id;
    Vector2 velocity = {0, 0};
    bool grounded;
    bool flip;
    Ray2D upRay;
    Ray2D downRay;
    Ray2D rightRay;
    Ray2D leftRay;
    PlayerState playerState;
    AnimationPlayer animationPlayer;
    Animation penguinIdleAnim = Animation(AssetManager::penguinIdle, 8, {{0, 0, 16, 16}, {16, 0, 16, 16}, {32, 0, 16, 16}, {48, 0, 16, 16}}, 4, PlayerState::IDLE);
    Animation penguinRunAnim = Animation(AssetManager::penguinRun, 16, {{0, 0, 16, 18}, {16, 0, 16, 18}, {32, 0, 16, 18}, {48, 0, 16, 18}}, 4, PlayerState::RUNNING);

    void handleInput();
    void applyPhysics();
    void updateAnimation();

public:
    Penguin();
    void update() override;
    void draw() override;
    void handleCollision(const Object& other) override;
    Vector2 getDimensions() const override;
};