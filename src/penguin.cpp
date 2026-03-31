#include "penguin.h"

constexpr int SPEED = 30;

Penguin::Penguin() : Object(Hitbox(std::make_unique<H_Rectangle>(pos.x, pos.y, 20, 40)))
{
    pos = (Vector2) {640, 360};
    grounded = false;
    id = 1;
}

void Penguin::update()
{
    handleInput();

    if (!grounded) velocity.y = 10;

    pos.x += velocity.x;
    pos.y += velocity.y;
    setHitboxPos(pos.x, pos.y);
}

void Penguin::draw()
{
    DrawRectangle(pos.x, pos.y, 20, 40, BLACK);
//    DrawRectangle(hitbox.collisionArea->x, hitbox.collisionArea->y, 20, 40, RED);
}

void Penguin::handleInput()
{
    int dir = (IsKeyDown(KEY_D) ? 1 : 0) + (IsKeyDown(KEY_A) ? -1 : 0);

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