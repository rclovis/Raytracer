/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Drop
*/

#pragma once
#include "PostProcessing.hpp"

extern "C" {
    std::string getType();
    std::string getId();
    IPostProcessing *Init();
}

class Drop : public IPostProcessing {
    public:
        Drop();
        ~Drop();
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
    return new Drop();
}

std::string getId ()
{
    return "drop";
}
