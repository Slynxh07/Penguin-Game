#include "world.h"
#include <iostream>

void World::update()
{
    for (auto& o : worldObjects)
    {
        o->update();
    }
}

void World::draw()
{
    for (auto& o : worldObjects)
    {
        o->draw();
    }
}

void World::addObject(std::unique_ptr<Object> obj)
{
    worldObjects.push_back(std::move(obj));
}