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
    int intensity = conf.lookup("r");
    _color = {{(float)r, (float)g, (float)b}};
    _intensity = (float)intensity;
}

Ambiant::~Ambiant()
{
}

lightColor Ambiant::getLight(normalRay ray)
{
    lightColor light;
    return light;
}