#include "hitbox.h"

bool H_Rectangle::collidesWith(const H_Shape& other) const
{
    return other.collidesWithRectangle(*this);
}

bool H_Circle::collidesWith(const H_Shape& other) const
{
    return other.collidesWithCircle(*this);
}


bool H_Circle::collidesWithCircle(const H_Circle& other) const
{

}

bool H_Circle::collidesWithRectangle(const H_Rectangle& other) const
{

}

bool H_Rectangle::collidesWithCircle(const H_Circle& other) const 
{

}

bool H_Rectangle::collidesWithRectangle(const H_Rectangle& other) const 
{

}