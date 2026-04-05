#include "spike.h"
#include <math.h>

void Spike::draw()
{
    DrawTriangle(verticies.at(0), verticies.at(1), verticies.at(2), color);
}

void Spike::update()
{

}

void Spike::handleCollision(const Object& other)
{

}

void Spike::updatePos()
{

}

Vector2 Spike::getDimensions() const
{
    return {abs(verticies.at(0).x - verticies.at(1).x), abs(verticies.at(2).y - verticies.at(0).y)};
}
