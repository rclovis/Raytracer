/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Ambient
*/

#pragma once
#include "PostProcessing.hpp"

extern "C" {
    std::string getType();
    std::string getId();
    IPostProcessing *Init();
}

class Ambient : public IPostProcessing {
    public:
        Ambient();
        ~Ambient();
        pixelColor getPixel (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray);

    protected:
    private:
};

std::string getType ()
{
    return "postProcessing";
}

IPostProcessing *Init()
{
    return new Ambient();
}

std::string getId ()
{
    return "ambient";
}
