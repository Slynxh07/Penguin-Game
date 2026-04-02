#include "platform.h"

void Platform::draw()
{
    DrawRectangleRec(rect, color);
}

void Platform::update()
{

}

void Platform::handleCollision(const Object& other)
{
    
}

Vector2 Platform::getDimensions() const
{
    return {this->rect.width, this->rect.height};
}