#pragma once

#include "raylib.h"
#include <vector>

class Animation {

public:

    Texture2D atlas;
    int fps;
    std::vector<Rectangle> rects;
    int length;
    int id;
    
    Animation(Texture2D atlas, int fps, std::vector<Rectangle> rects, int length, int id) : atlas(atlas), fps(fps), rects(rects), length(length), id(id) {}
};