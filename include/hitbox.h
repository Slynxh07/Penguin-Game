#pragma once

#include <memory>
#include "rays.h"

class H_Circle;
class H_Rectangle;

class H_Shape {

public:
    float x, y;
    H_Shape(float x, float y) : x(x), y(y) {}
    virtual ~H_Shape() {}

    virtual bool collidesWith(const H_Shape& other) const = 0;
    virtual bool collidesWithRay(const Ray2D& ray) const = 0;

    virtual bool collidesWithCircle(const H_Circle& other) const = 0;
    virtual bool collidesWithRectangle(const H_Rectangle& other) const = 0;

    virtual float findDistanceFromRay(const Ray2D ray) const = 0;

    virtual void draw() const = 0;
};

class H_Circle : public H_Shape {

public:
    float rad;
    H_Circle(float x, float y, float rad) : H_Shape(x, y), rad(rad) {}

    bool collidesWith(const H_Shape& other) const override;
    bool collidesWithRay(const Ray2D& ray) const override;

    bool collidesWithCircle(const H_Circle& other) const override;
    bool collidesWithRectangle(const H_Rectangle& other) const override;
    float findDistanceFromRay(const Ray2D ray) const override;

    void draw() const override;
};

class H_Rectangle : public H_Shape {

public:
    float width;
    float height;
    H_Rectangle(float x, float y, float width, float height) : H_Shape(x, y), width(width), height(height) {}

    bool collidesWith(const H_Shape& other) const override;
    bool collidesWithRay(const Ray2D& ray) const override;

    bool collidesWithCircle(const H_Circle& other) const override;
    bool collidesWithRectangle(const H_Rectangle& other) const override;
    float findDistanceFromRay(const Ray2D ray) const override;

    void draw() const override;
};

class Hitbox {
private:

public:
    std::unique_ptr<H_Shape> collisionArea;
    Hitbox(std::unique_ptr<H_Shape> shape)
        : collisionArea(std::move(shape)) {}

    bool isColliding(const Hitbox& other) const {
        return collisionArea->collidesWith(*other.collisionArea);
    }

    bool collidesWithRay(const Ray2D& ray) const {
        return collisionArea->collidesWithRay(ray);
    }

    float findDistanceFromRay(const Ray2D& ray) const {
        return collisionArea->findDistanceFromRay(ray);
    }

    void draw() const {
        collisionArea->draw();
    }
};