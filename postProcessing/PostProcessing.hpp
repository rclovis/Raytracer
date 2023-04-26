/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** PostProcessing
*/

#pragma once
#include <vector>
#include <map>
#include <string>
#include "struct.hpp"
#include "Primitives.hpp"
#include "Lights.hpp"

class IPostProcessing {
    public:
        virtual ~IPostProcessing() = default;
        virtual pixelColor getPixel (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray, cameraRay camera) = 0;
};
