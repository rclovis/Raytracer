/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Ambient
*/

#include "Ambient.hpp"

Ambient::Ambient()
{
}

Ambient::~Ambient()
{
}

pixelColor Ambient::getPixel (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray, cameraRay camera)
{
    pixelColor pixel;
    pixel.color = {{0, 0, 0}};
    for (auto &light : lights) {
        lightColor lightColor = light->getLight(ray);
        if (light->getLight(ray).id == 0) {
            pixel.color += (primitives[ray.primitiveId]->getColor() + lightColor.color) / 2 * lightColor.intensity;
            continue;
        }
    }
    pixel.color = mat::capMatrix(pixel.color, 1.0f);
    return pixel;
}