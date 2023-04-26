/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Diffuse
*/

#include "Diffuse.hpp"

Diffuse::Diffuse()
{
}

Diffuse::~Diffuse()
{
}

pixelColor Diffuse::getPixel (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray, cameraRay camera)
{
    pixelColor pixel;
    pixel.color = {{0, 0, 0}};
    for (auto &light : lights) {
        lightColor lightColor = light->getLight(ray);
        if (lightColor.direction == mat::Matrix<float, 1, 3>{{0, 0, 0}}) continue;
        mat::Matrix<float, 1, 3> tmp = (primitives[ray.primitiveId]->getColor() + lightColor.color) / 2 * lightColor.intensity;
        tmp *= std::max(0.0f, mat::dotProduct(ray.direction, lightColor.direction));
        pixel.color += tmp;
    }
    pixel.color = mat::capMatrix(pixel.color, 1.0f);
    return pixel;
}