#include "rays.h"
#include "objects.h"

Ray2DCollision Ray2D::GetCollisionInfo(const Object& other)
{
    Ray2DCollision collisionInfo = {false, 0 };
    collisionInfo.hit = other.collidesWithRay(*this);
    if (collisionInfo.hit)
    {
        collisionInfo.distance = other.findDistanceFromRay(*this);
    }
    return collisionInfo;
}

void Ray2D::draw()
{
    DrawLine(origin.x, origin.y, end.x, end.y, GREEN);
}

void Ray2D::updatePos(Vector2 newPos)
{
    origin = newPos;
    end = {origin.x + direction.x * length, origin.y + direction.y * length};
}