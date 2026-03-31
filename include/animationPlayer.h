#pragma once

#include "animation.h"
#include "raylib.h"
#include <optional>
#include <vector>

class AnimationPlayer {
public:
    AnimationPlayer();
    void setAnimation(Animation anim);
    void playAnimation(Rectangle dest, Vector2 origin, float rotation, Color tint, bool flip);
private:
    std::optional<Animation> anim;
    std::vector<Rectangle> rects;
};