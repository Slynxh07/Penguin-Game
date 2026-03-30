#pragma once

#include "raylib.h"
#include "hitbox.h"

#include <optional>

class Object {
    
private:
    int id;    
    Hitbox hitbox;

public:
    Object();
    Object(Hitbox hitbox);
    bool isColliding();
};