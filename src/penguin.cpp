#include "penguin.h"

constexpr int SPEED = 30;

Penguin::Penguin()
{
    id = 1;
}

void Penguin::update()
{
    handleInput();

    pos.x += velocity.x;
    pos.y += velocity.y;
    hitbox.collisionArea->x = pos.x;
    hitbox.collisionArea->y = pos.y;
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