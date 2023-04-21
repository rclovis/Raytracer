/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Circle
*/

#include "Circle.hpp"

Circle::Circle(libconfig::Setting &conf)
{
    int x = conf.lookup("x");
    int y = conf.lookup("y");
    int z = conf.lookup("z");
    int rad = conf.lookup("r");
    _position = {{(float)x, (float)y, (float)z}};
    _radius = (float)rad;
}

Circle::~Circle()
{
}

void Circle::computeIntersection (cameraRay ray)
{
    _ray.clear();
    float a = pow(ray.direction(0, 0), 2) + pow(ray.direction(0, 1), 2) + pow(ray.direction(0, 2), 2);
    float b = 2 * ray.direction(0, 0) * ray.origin(0, 0) + 2 * ray.direction(0, 1) * ray.origin(0, 1) + 2 * ray.direction(0, 2) * ray.origin(0, 2);
    float c = pow(ray.origin(0, 0), 2) + pow(ray.origin(0, 1), 2) + pow(ray.origin(0, 2), 2) - pow(_radius, 2);
    float delta = pow(b, 2) - 4 * a * c;
    if (delta < 0)
        return;
    float t1 = (-b + sqrt(delta)) / (2 * a);
    float t2 = (-b - sqrt(delta)) / (2 * a);
    float t = 0;
    if (t1 > 0) {
        normalRay normal;
        normal.origin = {{ray.origin(0, 0) + t1 * ray.direction(0, 0), ray.origin(0, 1) + t1 * ray.direction(0, 1), ray.origin(0, 2) + t1 * ray.direction(0, 2)}};
        normal.direction = {{ray.origin(0, 0) + t1 * ray.direction(0, 0), ray.origin(0, 1) + t1 * ray.direction(0, 1), ray.origin(0, 2) + t1 * ray.direction(0, 2)}};
        _ray.push_back(normal);
    } else if (t2 > 0) {
        normalRay normal;
        normal.origin = {{ray.origin(0, 0) + t2 * ray.direction(0, 0), ray.origin(0, 1) + t2 * ray.direction(0, 1), ray.origin(0, 2) + t2 * ray.direction(0, 2)}};
        normal.direction = {{ray.origin(0, 0) + t2 * ray.direction(0, 0), ray.origin(0, 1) + t2 * ray.direction(0, 1), ray.origin(0, 2) + t2 * ray.direction(0, 2)}};
        _ray.push_back(normal);
    } else {
        return;
    }
}

