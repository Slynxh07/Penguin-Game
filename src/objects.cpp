#include "objects.h"

bool Object::isColliding(const Object& other) const
{
    return hitbox.isColliding(other.hitbox);
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