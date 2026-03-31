#pragma once

#include "objects.h"

#include <vector>
#include <memory>

class World {

private:
    std::vector<std::unique_ptr<Object>> worldObjects;

public:
    World() = default;
    World(std::vector<std::unique_ptr<Object>> objects)
        : worldObjects(std::move(objects)) {}

    void update();
    void draw();
    void addObject(std::unique_ptr<Object> obj);
};