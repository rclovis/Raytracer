/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Directional
*/

#pragma once
#include "Lights.hpp"

extern "C" {
    std::string getType();
    std::string getId();
    ILights *Init(libconfig::Setting &conf);
}

class Directional : public ILights {
    public:
        Directional(libconfig::Setting &conf);
        ~Directional();
        lightColor getLight(normalRay ray);

    private:
        mat::Matrix<float, 1, 3> _color;
        mat::Matrix<float, 1, 3> _direction;
        float _intensity;
};


std::string getType ()
{
    return "light";
}

ILights *Init(libconfig::Setting &conf)
{
    return new Directional(conf);
}

std::string getId ()
{
    return "directional";
}