#include "world.h"
#include <iostream>

void World::update()
{
    for (auto& o : worldObjects)
    {
        o->update();
    }

    for (int i = 0; i < worldObjects.size(); i++)
    {
        for (int j = i + 1; j < worldObjects.size(); j++)
        {
            if (worldObjects.at(i)->isColliding(*worldObjects.at(j)))
            {
                worldObjects.at(i)->handleCollision(*worldObjects.at(j));
            }
        }
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