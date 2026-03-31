#include "penguin.h"
#include "assetManager.h"

constexpr int SPEED = 15;

Penguin::Penguin() : Object(Hitbox(std::make_unique<H_Rectangle>(pos.x, pos.y, 40, 40)))
{
    pos = (Vector2) {640, 360};
    grounded = false;
    flip = false;
    id = 1;
    animationPlayer.setAnimation(penguinIdleAnim);
}

void Penguin::update()
{
    handleInput();

    if (!grounded) velocity.y += 5;

    pos.x += velocity.x;
    pos.y += velocity.y;
    setHitboxPos(pos.x, pos.y);
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

    if (IsKeyPressed(KEY_SPACE))
    {
        velocity.y = -40;
        grounded = false;
    }

    if (dir) velocity.x = dir * SPEED;
    else velocity.x = 0;
}

void Penguin::handleCollision(const Object& other)
{
    if(other.getPos().y <= pos.y + 40)
    {
        velocity.y = 0;
        pos.y = other.getPos().y - 40;
        grounded = true;
    }
}