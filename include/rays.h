#pragma once

#include "raylib.h"

class Object;

typedef struct Ray2DCollision {
    bool hit;
    float distance;
    Vector2 normal;
} Ray2DCollision;


class Ray2D {

public:
    Vector2 origin;
    Vector2 direction;
    Vector2 end;
    float length;
    void draw();
    void updatePos(Vector2 newPos);
    Ray2DCollision GetCollisionInfo(const Object& other);
    Ray2D() = default;
    Ray2D(Vector2 origin, Vector2 direction, float length) : origin(origin), direction(direction), length(length) 
    { end = {origin.x + direction.x * length, origin.y + direction.y * length}; }
};