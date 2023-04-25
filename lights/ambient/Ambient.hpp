/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Ambiant
*/

#pragma once
#include "Lights.hpp"

extern "C" {
    std::string getType();
    std::string getId();
    ILights *Init(libconfig::Setting &conf);
}

class Ambiant : public ILights {
    public:
        Ambiant(libconfig::Setting &conf);
        ~Ambiant();
        lightColor getLight(normalRay ray);

    private:
        mat::Matrix<float, 1, 3> _color;
        float _intensity;
};


std::string getType ()
{
    return "light";
}

ILights *Init(libconfig::Setting &conf)
{
    return new Ambiant(conf);
}

std::string getId ()
{
    return "ambient";
}