#include "penguin.h"
#include "assetManager.h"
#include "math.h"
#include <iostream>

constexpr float SPEED = 2.5f;
constexpr int JUMP_POWER = 30;
constexpr int GRAVITY = 5;
constexpr float RAY_BUFFER = 5.0f;

Penguin::Penguin() : Object(Hitbox(std::make_unique<H_Rectangle>(pos.x, pos.y, 40, 40)))
{
    pos = {640, 575};
    grounded = false;
    flip = false;
    id = 1;
    playerState = PlayerState::IDLE;
    upRay = Ray2D({ pos.x + 20, pos.y + 2.5f, }, { 0, -1 }, 15);
    downRay = Ray2D({ pos.x + 20, pos.y + 37.5f, }, { 0, 1 }, 15);
    rightRay = Ray2D({ pos.x + 37.5f, pos.y + 20,}, { 1, 0 }, 15);
    leftRay = Ray2D({ pos.x + 2.5f, pos.y + 20, }, { -1, 0 }, 15);
    animationPlayer.setAnimation(penguinIdleAnim);
}

void Penguin::update()
{
    handleInput();
    applyPhysics();
    grounded = false;
}

void Penguin::updatePos()
{
    pos.x += velocity.x;
    pos.y += velocity.y;
    setHitboxPos(pos.x, pos.y);

    upRay.length = fabs(velocity.y) + RAY_BUFFER;
    downRay.length = fabs(velocity.y) + RAY_BUFFER;
    rightRay.length = fabs(velocity.x) + RAY_BUFFER;
    leftRay.length = fabs(velocity.x) + RAY_BUFFER;

    upRay.updatePos({pos.x + 20, pos.y + 2.5f});
    downRay.updatePos({pos.x + 20, pos.y + 37.5f});
    rightRay.updatePos({pos.x + 37.5f, pos.y + 20});
    leftRay.updatePos({pos.x + 2.5f, pos.y + 20});

    updateAnimation();
}

void Penguin::draw()
{
    animationPlayer.playAnimation({pos.x, pos.y, 40, 40}, {0, 0}, 0, WHITE, flip);
}

void Penguin::handleInput()
{
    int dir = (IsKeyDown(KEY_D) ? 1 : 0) + (IsKeyDown(KEY_A) ? -1 : 0);
    if (dir > 0) flip = true;
    else if (dir < 0) flip = false;

    if (IsKeyPressed(KEY_SPACE) && grounded)
    {
        velocity.y = -JUMP_POWER;
        grounded = false;
    }

    if (dir) velocity.x = dir * SPEED;
    else velocity.x = 0;
}

void Penguin::applyPhysics()
{
    if (!grounded) velocity.y += GRAVITY;
    else velocity.y = 0;
}

void Penguin::updateAnimation()
{
    PlayerState newState;

    if (velocity.x != 0)
        newState = PlayerState::RUNNING;
    else
        newState = PlayerState::IDLE;

    if (newState != playerState)
    {
        playerState = newState;

        switch (playerState)
        {
            case PlayerState::IDLE: animationPlayer.setAnimation(penguinIdleAnim); break;
            case PlayerState::RUNNING: animationPlayer.setAnimation(penguinRunAnim); break;
            default: break;
        }    
    }
}

void Penguin::handleCollision(const Object& other)
{
    Ray2DCollision upCol = upRay.GetCollisionInfo(other);
    Ray2DCollision downCol = downRay.GetCollisionInfo(other);
    Ray2DCollision rightCol = rightRay.GetCollisionInfo(other);
    Ray2DCollision leftCol = leftRay.GetCollisionInfo(other);

    const float epsilon = 0.1f;

    if (velocity.y < 0 && upCol.hit && upCol.distance >= 0 && upCol.distance <= fabs(velocity.y) + 1)
    {
        velocity.y = 0;
        pos.y = other.getPos().y + other.getDimensions().y + epsilon;
    }
    
    if (velocity.y >= 0 && downCol.hit && downCol.distance <= downRay.length)
    {
        velocity.y = 0;
        pos.y = other.getPos().y - 40 + epsilon;
        grounded = true;
    }

    if (velocity.x > 0 && rightCol.hit && rightCol.distance >= 0 && rightCol.distance <= fabs(velocity.x) + 1)
    {
        velocity.x = 0;
        pos.x = other.getPos().x - 40 - epsilon;
    }
    else if (velocity.x < 0 && leftCol.hit && leftCol.distance >= 0 && leftCol.distance <= fabs(velocity.x) + 1)
    {
        velocity.x = 0;
        pos.x = other.getPos().x + other.getDimensions().x + epsilon;
    }

    setHitboxPos(pos.x, pos.y);
}

Vector2 Penguin::getDimensions() const
{
    return {40, 40};
}