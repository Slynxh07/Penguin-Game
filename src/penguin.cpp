#include "penguin.h"
#include "assetManager.h"

constexpr float SPEED = 2.5f;
constexpr int JUMP_POWER = 30;
constexpr int GRAVITY = 5;

Penguin::Penguin() : Object(Hitbox(std::make_unique<H_Rectangle>(pos.x, pos.y, 40, 40)))
{
    pos = (Vector2) {640, 575};
    grounded = false;
    flip = false;
    id = 1;
    playerState = PlayerState::IDLE;
    upRay = Ray2D({ pos.x + 20, pos.y + 2.5f, }, { 0, -1 }, 20);
    downRay = Ray2D({ pos.x + 20, pos.y + 37.5f, }, { 0, 1 }, 20);
    rightRay = Ray2D({ pos.x + 37.5f, pos.y + 20,}, { 1, 0 }, 20);
    leftRay = Ray2D({ pos.x + 2.5f, pos.y + 20, }, { -1, 0 }, 20);
    animationPlayer.setAnimation(penguinIdleAnim);
}

void Penguin::update()
{
    handleInput();
    applyPhysics();

    pos.x += velocity.x;
    pos.y += velocity.y;
    setHitboxPos(pos.x, pos.y);

    upRay.updatePos({pos.x + 20, pos.y + 2.5f});
    downRay.updatePos({pos.x + 20, pos.y + 37.5f});
    rightRay.updatePos({pos.x + 37.5f, pos.y + 20});
    leftRay.updatePos({pos.x + 2.5f, pos.y + 20});

    updateAnimation();
}

void Penguin::draw()
{
    animationPlayer.playAnimation({pos.x, pos.y, 40, 40}, {0, 0}, 0, WHITE, flip);
    upRay.draw();
    downRay.draw();
    rightRay.draw();
    leftRay.draw();
}

void Penguin::handleInput()
{
    int dir = (IsKeyDown(KEY_D) ? 1 : 0) + (IsKeyDown(KEY_A) ? -1 : 0);
    if (dir > 0) flip = true;
    else if (dir < 0) flip = false;

    if (IsKeyPressed(KEY_SPACE))
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
    if(other.getPos().y >= pos.y)
    {
        velocity.y = 0;
        pos.y = other.getPos().y - 40;
        grounded = true;
    }
    else if (other.getPos().y <= pos.y)
    {
        velocity.y = 0;
        pos.y = other.getPos().y + other.getDimensions().y;
    }
    setHitboxPos(pos.x, pos.y);
}

Vector2 Penguin::getDimensions() const
{
    return {40, 40};
}