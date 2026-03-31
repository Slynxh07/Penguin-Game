#pragma once

#include "raylib.h"
#include "hitbox.h"

#include <memory>

class Object {
    
private:
    int id;    
    Hitbox hitbox;

protected:
    Vector2 pos;

public:
    virtual ~Object() = default;
    Object(Hitbox hitbox) : hitbox(std::move(hitbox)) {}
    bool isColliding(const Object& other) const;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void handleCollision(const Object& other) = 0;
    void setHitboxPos(float x, float y);
    Vector2 getPos() const;
};