/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Ambiant
*/

#include "Ambient.hpp"

Ambiant::Ambiant(libconfig::Setting &conf)
{
    int r = conf.lookup("r");
    int g = conf.lookup("g");
    int b = conf.lookup("b");
    float intensity = conf.lookup("m");
    _color = {{(float)r, (float)g, (float)b}};
    _color = _color / 255;
    _intensity = intensity;
}

Ambiant::~Ambiant()
{
}

lightColor Ambiant::getLight(normalRay ray)
{
    lightColor light;
    light.color = _color;
    light.direction = {{0, 0, 0}};
    light.origin = {{0, 0, 0}};
    light.intensity = _intensity;
    light.id = 0;
    return light;
}