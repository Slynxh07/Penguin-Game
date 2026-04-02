#include "hitbox.h"
#include "raylib.h"
#include "math.h"

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

bool H_Rectangle::collidesWithRay(const Ray2D& ray) const
{
    Vector2 topLeft = { x, y };
    Vector2 topRight = { x + width, y };
    Vector2 bottomLeft = { x, y + height };
    Vector2 bottomRight = { x + width, y + height };

    Vector2 collisionPoint;

    return
        CheckCollisionLines(ray.origin, ray.end, topLeft, topRight, &collisionPoint) ||
        CheckCollisionLines(ray.origin, ray.end, topRight, bottomRight, &collisionPoint) ||
        CheckCollisionLines(ray.origin, ray.end, bottomRight, bottomLeft, &collisionPoint) ||
        CheckCollisionLines(ray.origin, ray.end, bottomLeft, topLeft, &collisionPoint);
}

bool H_Circle::collidesWithRay(const Ray2D& ray) const
{
    return CheckCollisionCircleLine({x, y}, rad, ray.origin, ray.end);
}

float H_Rectangle::findDistanceFromRay(const Ray2D ray) const
{
    Vector2 topLeft = { x, y };
    Vector2 topRight = { x + width, y };
    Vector2 bottomLeft = { x, y + height };
    Vector2 bottomRight = { x + width, y + height };

    Vector2 collisionPoint;

    CheckCollisionLines(ray.origin, ray.end, topLeft, topRight, &collisionPoint);
    CheckCollisionLines(ray.origin, ray.end, topRight, bottomRight, &collisionPoint);
    CheckCollisionLines(ray.origin, ray.end, bottomRight, bottomLeft, &collisionPoint);
    CheckCollisionLines(ray.origin, ray.end, bottomLeft, topLeft, &collisionPoint);

    float xLen = abs(collisionPoint.x - ray.origin.x);
    float yLen = abs(collisionPoint.y - ray.origin.y);

    return (xLen * xLen) + (yLen * yLen);
}

float H_Circle::findDistanceFromRay(const Ray2D ray) const
{
    Vector2 oc;
    oc.x = ray.origin.x - this->x;
    oc.y = ray.origin.y - this->y;

    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
    float b = 2.0f * (oc.x * ray.direction.x + oc.y * ray.direction.y);
    float c = oc.x * oc.x + oc.y * oc.y - this->rad * this->rad;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return -1.0f;

    float sqrtD = sqrt(discriminant);
    float t1 = (-b - sqrtD) / (2.0f * a);
    float t2 = (-b + sqrtD) / (2.0f * a);

    if (t1 >= 0) return t1;
    if (t2 >= 0) return t2;

    return -1.0f;
}