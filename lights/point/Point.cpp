/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Point
*/

#include "Point.hpp"

Point::Point(libconfig::Setting &conf)
{
    int r = conf.lookup("r");
    int g = conf.lookup("g");
    int b = conf.lookup("b");
    int x = conf.lookup("x");
    int y = conf.lookup("y");
    int z = conf.lookup("z");
    float intensity = conf.lookup("m");
    _color = {{(float)r, (float)g, (float)b}};
    _color = _color / 255;
    _intensity = intensity;
    _direction = {{(float)x, (float)y, (float)z}};
}

Point::~Point()
{
}

lightColor Point::getLight(normalRay ray)
{
    lightColor light;
    light.color = _color;
    light.direction = mat::normalizeVector(_direction - ray.origin);
    light.origin = {{0, 0, 0}};
    light.intensity = _intensity;
    light.id = 1;
    return light;
}
