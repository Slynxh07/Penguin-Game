#pragma once

#include "raylib.h"
#include <vector>

class Animation {

public:

    std::vector<Rectangle> rects;
    Texture2D atlas;
    int fps;
    int length;
    int id;
    
    Animation(Texture2D atlas, int fps, std::vector<Rectangle> rects, int length, int id) : atlas(atlas), fps(fps), length(length), id(id), rects(rects) {}
};