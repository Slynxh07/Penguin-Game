#include "objects.h"

bool Object::isColliding(const Object& other) const
{
    return hitbox.isColliding(other.hitbox);
}

void Object::setHitbox(const Hitbox hb)
{
    return;
    //hitbox = std::move(hb);
}