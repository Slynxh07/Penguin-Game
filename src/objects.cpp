#include "objects.h"

bool Object::isColliding(const Object& other) const
{
    return hitbox.isColliding(other.hitbox);
}

bool Object::collidesWithRay(const Ray2D &ray) const
{
    return hitbox.collidesWithRay(ray);
}

void Object::setHitboxPos(float x, float y)
{
    hitbox.collisionArea->x = x;
    hitbox.collisionArea->y = y;
}

Vector2 Object::getPos() const
{
    return pos;
}

float Object::findDistanceFromRay(const Ray2D& ray) const
{
    return hitbox.findDistanceFromRay(ray);
}