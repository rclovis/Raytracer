/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Diffuse
*/

#pragma once
#include "PostProcessing.hpp"

extern "C" {
    std::string getType();
    std::string getId();
    IPostProcessing *Init();
}

class Diffuse : public IPostProcessing {
    public:
        Diffuse();
        ~Diffuse();
        pixelColor getPixel (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray, cameraRay camera);

    protected:
    private:
};

std::string getType ()
{
    return "postProcessing";
}

IPostProcessing *Init()
{
    return new Diffuse();
}

std::string getId ()
{
    return "diffuse";
}
