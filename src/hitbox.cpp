#include "hitbox.h"
#include "raylib.h"
#include "math.h"
#include <float.h>

float cross(const Vector2& a, const Vector2& b) {
    return a.x * b.y - a.y * b.x;
}

Vector2 subtract(const Vector2& a, const Vector2& b) {
    return {a.x - b.x, a.y - b.y};
}

float dot(const Vector2& a, const Vector2& b) {
    return a.x * b.x + a.y * b.y;
}

bool segmentsIntersect(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2) {
    Vector2 r = subtract(p2, p1);
    Vector2 s = subtract(q2, q1);

    float denom = cross(r, s);
    float numer1 = cross(subtract(q1, p1), r);
    float numer2 = cross(subtract(q1, p1), s);

    if (denom == 0) return false;

    float t = numer2 / denom;
    float u = numer1 / denom;

    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

bool pointInTriangle(Vector2 p, Vector2 a, Vector2 b, Vector2 c) {
    Vector2 v0 = subtract(c, a);
    Vector2 v1 = subtract(b, a);
    Vector2 v2 = subtract(p, a);

    float dot00 = dot(v0, v0);
    float dot01 = dot(v0, v1);
    float dot02 = dot(v0, v2);
    float dot11 = dot(v1, v1);
    float dot12 = dot(v1, v2);

    float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);

    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

float distPointToSegment(Vector2 p, Vector2 a, Vector2 b) {
    Vector2 ab = subtract(b, a);
    Vector2 ap = subtract(p, a);

    float t = dot(ap, ab) / dot(ab, ab);
    t = std::max(0.0f, std::min(1.0f, t));

    Vector2 closest = {a.x + ab.x * t, a.y + ab.y * t};
    Vector2 diff = subtract(p, closest);

    return std::sqrt(dot(diff, diff));
}

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
    return CheckCollisionCircles({this->x, this->y}, this->rad, {other.x, other.y}, other.rad);
}

bool H_Circle::collidesWithRectangle(const H_Rectangle& other) const
{
    return CheckCollisionCircleRec({this->x, this->y}, this->rad, {other.x, other.y, other.width, other.height});
}

bool H_Rectangle::collidesWithCircle(const H_Circle& other) const 
{
    return CheckCollisionCircleRec({other.x, other.y}, other.rad, {this->x, this->y, this->width, this->height});
}

bool H_Rectangle::collidesWithRectangle(const H_Rectangle& other) const 
{
    return CheckCollisionRecs({this->x, this->y, this->width, this->height}, {other.x, other.y, other.width, other.height});
}

bool H_Triangle::collidesWith(const H_Shape& other) const
{
    return other.collidesWithTriangle(*this);
}

bool H_Triangle::collidesWithTriangle(const H_Triangle& other) const {
    for (int i = 0; i < 3; i++) {
        Vector2 p1 = verticies[i];
        Vector2 p2 = verticies[(i + 1) % 3];

        for (int j = 0; j < 3; j++) {
            Vector2 q1 = other.verticies[j];
            Vector2 q2 = other.verticies[(j + 1) % 3];

            if (segmentsIntersect(p1, p2, q1, q2))
                return true;
        }
    }

    if (pointInTriangle(verticies.at(0), other.verticies.at(0), other.verticies.at(1), other.verticies.at(2))) return true;
    if (pointInTriangle(other.verticies.at(0), verticies.at(0), verticies.at(1), verticies.at(2))) return true;

    return false;
}

bool H_Rectangle::collidesWithTriangle(const H_Triangle& other) const {
    Vector2 r1 = {x, y};
    Vector2 r2 = {x + width, y};
    Vector2 r3 = {x + width, y + height};
    Vector2 r4 = {x, y + height};

    H_Triangle t1(r1, r2, r3);
    H_Triangle t2(r1, r3, r4);

    return t1.collidesWithTriangle(other) || t2.collidesWithTriangle(other);
}

bool H_Circle::collidesWithTriangle(const H_Triangle& other) const {
    if (pointInTriangle({x, y}, other.verticies.at(0), other.verticies.at(1), other.verticies.at(2)))
        return true;

    if (distPointToSegment({x, y}, other.verticies.at(0), other.verticies.at(1)) <= rad) return true;
    if (distPointToSegment({x, y}, other.verticies.at(1), other.verticies.at(2)) <= rad) return true;
    if (distPointToSegment({x, y}, other.verticies.at(2), other.verticies.at(0)) <= rad) return true;

    return false;
}

bool H_Rectangle::collidesWithRay(const Ray2D& ray) const
{
    Vector2 topLeft = { x, y };
    Vector2 topRight = { x + width, y };
    Vector2 bottomLeft = { x, y + height };
    Vector2 bottomRight = { x + width, y + height };

    Vector2 collisionPoint;

    return
        CheckCollisionLines(ray.origin, ray.end, topLeft, topRight, &collisionPoint) ||
        CheckCollisionLines(ray.origin, ray.end, topRight, bottomRight, &collisionPoint) ||
        CheckCollisionLines(ray.origin, ray.end, bottomRight, bottomLeft, &collisionPoint) ||
        CheckCollisionLines(ray.origin, ray.end, bottomLeft, topLeft, &collisionPoint);
}

bool H_Circle::collidesWithRay(const Ray2D& ray) const
{
    return CheckCollisionCircleLine({x, y}, rad, ray.origin, ray.end);
}

float H_Rectangle::findDistanceFromRay(const Ray2D ray) const
{
    Vector2 topLeft = { x, y };
    Vector2 topRight = { x + width, y };
    Vector2 bottomLeft = { x, y + height };
    Vector2 bottomRight = { x + width, y + height };

    float minDist = FLT_MAX;
    bool hit = false;

    auto checkEdge = [&](Vector2 a, Vector2 b)
    {
        Vector2 point;
        if (CheckCollisionLines(ray.origin, ray.end, a, b, &point))
        {
            float dx = point.x - ray.origin.x;
            float dy = point.y - ray.origin.y;
            float dist = dx * dx + dy * dy;

            if (dist < minDist)
            {
                minDist = dist;
                hit = true;
            }
        }
    };

    checkEdge(topLeft, topRight);
    checkEdge(topRight, bottomRight);
    checkEdge(bottomRight, bottomLeft);
    checkEdge(bottomLeft, topLeft);

    minDist = sqrt(minDist);

    return hit ? minDist : -1.0f;
}

float H_Circle::findDistanceFromRay(const Ray2D ray) const
{
    Vector2 oc;
    oc.x = ray.origin.x - this->x;
    oc.y = ray.origin.y - this->y;

    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
    float b = 2.0f * (oc.x * ray.direction.x + oc.y * ray.direction.y);
    float c = oc.x * oc.x + oc.y * oc.y - this->rad * this->rad;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return -1.0f;

    float sqrtD = sqrt(discriminant);
    float t1 = (-b - sqrtD) / (2.0f * a);
    float t2 = (-b + sqrtD) / (2.0f * a);

    if (t1 >= 0) return t1;
    if (t2 >= 0) return t2;

    return -1.0f;
}

void H_Circle::draw() const
{
    DrawCircle(x, y, rad, RED);
}

void H_Rectangle::draw() const
{
    DrawRectangle(x, y, width, height, RED);
}

void H_Triangle::draw() const 
{
    DrawTriangle(verticies.at(0), verticies.at(1), verticies.at(2), RED);
}

bool H_Triangle::collidesWithRectangle(const H_Rectangle& other) const
{
    return other.collidesWithTriangle(*this);
}

bool H_Triangle::collidesWithCircle(const H_Circle& other) const
{
    return other.collidesWithTriangle(*this);
}

bool H_Triangle::collidesWithRay(const Ray2D& ray) const
{
    Vector2 collisionPoint;

    return
        CheckCollisionLines(ray.origin, ray.end, verticies.at(0), verticies.at(1), &collisionPoint) ||
        CheckCollisionLines(ray.origin, ray.end, verticies.at(0), verticies.at(2), &collisionPoint) ||
        CheckCollisionLines(ray.origin, ray.end, verticies.at(1), verticies.at(2), &collisionPoint);
}

float H_Triangle::findDistanceFromRay(const Ray2D ray) const
{
    float minDist = FLT_MAX;
    bool hit = false;

    auto checkEdge = [&](Vector2 a, Vector2 b)
    {
        Vector2 point;
        if (CheckCollisionLines(ray.origin, ray.end, a, b, &point))
        {
            float dx = point.x - ray.origin.x;
            float dy = point.y - ray.origin.y;
            float dist = dx * dx + dy * dy;

            if (dist < minDist)
            {
                minDist = dist;
                hit = true;
            }
        }
    };

    checkEdge(verticies[0], verticies[1]);
    checkEdge(verticies[1], verticies[2]);
    checkEdge(verticies[2], verticies[0]);

    minDist = sqrt(minDist);

    return hit ? minDist : -1.0f;
}