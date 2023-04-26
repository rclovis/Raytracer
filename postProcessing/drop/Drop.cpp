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

pixelColor Drop::getPixel (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray, cameraRay camera)
{
    pixelColor pixel;
    pixel.color = {{0, 0, 0}};
    for (auto &light : lights) {
        lightColor lightColor = light->getLight(ray);
        if (lightColor.direction == mat::Matrix<float, 1, 3>{{0, 0, 0}}) continue;
        cameraRay lightRay;
        lightRay.origin = ray.origin + ray.direction * 0.01;
        lightRay.direction = lightColor.direction;
        std::vector<normalRay> lightRays;
        for (auto &primitive : primitives) {
            primitive->computeIntersection(lightRay);
            for (auto &intersection : primitive->getIntersection()) {
                lightRays.push_back(intersection);
            }
        }
        if (lightRays.size() == 0) {
            mat::Matrix<float, 1, 3> objectColor = primitives[ray.primitiveId]->getColor();
            mat::Matrix<float, 1, 3> tmp = {{
                objectColor(0, 0) * (1.0f - lightColor.intensity) + lightColor.color(0, 0) * lightColor.intensity,
                objectColor(0, 1) * (1.0f - lightColor.intensity) + lightColor.color(0, 1) * lightColor.intensity,
                objectColor(0, 2) * (1.0f - lightColor.intensity) + lightColor.color(0, 2) * lightColor.intensity
            }};


            tmp *= std::max(0.0f, mat::dotProduct(ray.direction, lightColor.direction));

            mat::Matrix<float, 1, 3> specular = {{0, 0, 0}};
            mat::Matrix<float, 1, 3> reflection = mat::normalizeVector(mat::reflectVector(camera.direction, ray.direction));
            float specularIntensity = std::pow(std::max(0.0f, mat::dotProduct(reflection, lightColor.direction)), 32);
            specular = mat::capMatrix(mat::Matrix<float, 1, 3> {{
                specularIntensity, specularIntensity, specularIntensity
            }}, 1.0f);
            tmp += specular;

            pixel.color += tmp;
        }
    }
    pixel.color = mat::capMatrix(pixel.color, 1.0f);
    return pixel;
}