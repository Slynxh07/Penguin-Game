#include "animationPlayer.h"

AnimationPlayer::AnimationPlayer()
{
    anim = std::nullopt;
}

void AnimationPlayer::setAnimation(Animation anim)
{
    if (this->anim.has_value() && this->anim.value().id == anim.id) return;
    this->anim = anim;
    this->rects = anim.rects;
}

void AnimationPlayer::playAnimation(Rectangle dest, Vector2 origin, float rotation, Color tint, bool flip)
{
    if (!anim.has_value()) return;

    int i = (int) (GetTime() * anim->fps) % anim->length;
    Rectangle source = rects.at(i);

    if (flip)
    {
        source.x += source.width;
        source.width *= -1;
    }

    DrawTexturePro(anim->atlas, source, dest, origin, rotation, tint);
}