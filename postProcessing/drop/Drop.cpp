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
    int i = 0;
    for (auto &light : lights) {
        lightColor lightColor = light->getLight(ray);
        if (light->getLight(ray).id == 0) {
            pixel.color += (primitives[ray.primitiveId]->getColor() + lightColor.color) / 2 * lightColor.intensity;
            i++;
            continue;
        }
        cameraRay lightRay;
        lightRay.origin = ray.origin + ray.direction;
        lightRay.direction = lightColor.direction * -1;
        std::vector<normalRay> lightRays;
        for (auto &primitive : primitives) {
            primitive->computeIntersection(lightRay);
            for (auto &intersection : primitive->getIntersection()) {
                lightRays.push_back(intersection);
            }
        }

        if (lightRays.size() == 0) {
            printf("cfv\n");
            pixel.color += (primitives[ray.primitiveId]->getColor() + lightColor.color) / 2 * lightColor.intensity;
            i++;
        }
    }
    pixel.color /= i;
    return pixel;
}