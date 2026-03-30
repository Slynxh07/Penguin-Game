#pragma once

#include <objects.h>

#include <vector>

class World {

private:
    std::vector<Object> worldObjects;

public:
    World();
    World(const std::vector<Object> objects);
    void update();
    void draw();
};