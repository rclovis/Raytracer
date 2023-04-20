/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Circle
*/

#include "Circle.hpp"

Circle::Circle(Matrix<float, 1, 3> position, float radius)
{
    _position = position;
    _radius = radius;
}

Circle::~Circle()
{
}

void Circle::computeIntersection (cameraRay ray)
{
    _ray.clear();
    float a = pow(ray.direction(0, 0), 2) + pow(ray.direction(0, 1), 2);
    float b = 2 * (ray.direction(0, 0) * ray.origin(0, 0) + ray.direction(0, 1) * ray.origin(0, 1));
    float c = pow(ray.origin(0, 0), 2) + pow(ray.origin(0, 1), 2) - pow(_radius, 2);
    float delta = pow(b, 2) - 4 * a * c;
    float t1 = (-b + sqrt(delta)) / (2 * a);
    float t2 = (-b - sqrt(delta)) / (2 * a);
    float t = 0;
    if (t1 > 0 && t2 > 0)
        t = (t1 < t2) ? t1 : t2;
    else if (t1 > 0) {
        t = t1;
        normalRay normal;
        normal.origin = {{ray.origin(0, 0) + t * ray.direction(0, 0), ray.origin(0, 1) + t * ray.direction(0, 1), ray.origin(0, 2) + t * ray.direction(0, 2)}};
        normal.direction = {{ray.origin(0, 0) + t * ray.direction(0, 0), ray.origin(0, 1) + t * ray.direction(0, 1), ray.origin(0, 2) + t * ray.direction(0, 2)}};
        _ray.push_back(normal);
    } else if (t2 > 0) {
        t = t2;
        normalRay normal;
        normal.origin = {{ray.origin(0, 0) + t * ray.direction(0, 0), ray.origin(0, 1) + t * ray.direction(0, 1), ray.origin(0, 2) + t * ray.direction(0, 2)}};
        normal.direction = {{ray.origin(0, 0) + t * ray.direction(0, 0), ray.origin(0, 1) + t * ray.direction(0, 1), ray.origin(0, 2) + t * ray.direction(0, 2)}};
        _ray.push_back(normal);
    } else
        return;
}

