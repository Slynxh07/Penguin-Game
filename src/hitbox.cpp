#include "hitbox.h"
#include "raylib.h"

bool H_Rectangle::collidesWith(const H_Shape& other) const
{
    return other.collidesWithRectangle(*this);
}

bool H_Circle::collidesWith(const H_Shape& other) const
{
    return other.collidesWithCircle(*this);
}


bool H_Circle::collidesWithCircle(const H_Circle& other) const
{
    return CheckCollisionCircles({this->x, this->y}, this->rad, {other.x, other.y}, other.rad);
}

bool H_Circle::collidesWithRectangle(const H_Rectangle& other) const
{
    return CheckCollisionCircleRec({this->x, this->y}, this->rad, {other.x, other.y, other.width, other.height});
}

bool H_Rectangle::collidesWithCircle(const H_Circle& other) const 
{
    return CheckCollisionCircleRec({other.x, other.y}, other.rad, {this->x, this->y, this->width, this->height});
}

bool H_Rectangle::collidesWithRectangle(const H_Rectangle& other) const 
{
    return CheckCollisionRecs({this->x, this->y, this->width, this->height}, {other.x, other.y, other.width, other.height});
}