/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Drop
*/

#include "Drop.hpp"

Drop::Drop()
{
}

Drop::~Drop()
{
}

pixelColor Drop::getPixel (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray)
{
    pixelColor pixel;
    pixel.color = {{0, 0, 0}};
    for (auto &light : lights) {
        lightColor lightColor = light->getLight(ray);
        if (lightColor.direction == mat::Matrix<float, 1, 3>{{0, 0, 0}})
            continue;
        // if (light->getLight(ray).id == 0) {
        //     pixel.color += (primitives[ray.primitiveId]->getColor() + lightColor.color) / 2 * lightColor.intensity;
        //     continue;
        // }
        cameraRay lightRay;
        lightRay.origin = ray.origin + ray.direction * 0.1;
        lightRay.direction = lightColor.direction;
        std::vector<normalRay> lightRays;
        for (auto &primitive : primitives) {
            primitive->computeIntersection(lightRay);
            for (auto &intersection : primitive->getIntersection()) {
                lightRays.push_back(intersection);
            }
        }
        if (lightRays.size() == 0) {
            pixel.color += (primitives[ray.primitiveId]->getColor() + lightColor.color) / 2 * lightColor.intensity;
        }
    }
    pixel.color = mat::capMatrix(pixel.color, 1.0f);
    return pixel;
}