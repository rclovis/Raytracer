/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Shading
*/

#include "Shading.hpp"

Shading::Shading()
{
}

Shading::~Shading()
{
}

mat::Matrix<float, 1, 3> Shading::shadingPipeline (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, std::vector<normalRay> ray, cameraRay camera)
{
    mat::Matrix<float, 1, 3> finalColor = {{0, 0, 0}};
    if (ray.size() == 0) return finalColor;
    finalColor = {{0, 0, 0}};
    for (auto &light : lights) {
        //recupérer le rayon de limière (contient la direction et la couleur)
        lightColor lightColor = light->getLight(ray[0]);
        //

        //calculer l'intersection entre le rayon de lumière et les primitives (si l'endroit touché est dans l'ombre, ou pas)
        cameraRay lightRay;
        lightRay.origin = ray[0].origin + ray[0].direction * 0.01;
        lightRay.direction = lightColor.direction;
        std::vector<normalRay> intersections;
        int id = 0;
        for (auto &primitive : primitives) {
            std::vector<normalRay> intersec = primitive->computeIntersection(lightRay);
            for (auto &intersection : intersec) {
                intersection.primitiveId = id;
                intersection.distance = sqrt(pow(intersection.origin(0, 0) - lightRay.origin(0, 0), 2) + pow(intersection.origin(0, 1) - lightRay.origin(0, 1), 2) + pow(intersection.origin(0, 2) - lightRay.origin(0, 2), 2));
                intersections.push_back(intersection);
            }
            id++;
        }
        std::sort(intersections.begin(), intersections.end(), [](const normalRay &a, const normalRay &b) {
            return a.distance < b.distance;
        });
        float opacity = 0;
        for (auto &intersection : intersections) {
            opacity += primitives[intersection.primitiveId]->getMaterial().transparency * (1 - opacity);
            lightColor.color = mixColor(lightColor.color, primitives[intersection.primitiveId]->getMaterial().color, lightColor.intensity);
        }
        if (opacity >= 1) {
            continue;
        }
        //

        mat::Matrix<float, 1, 3> objectColor = primitives[ray[0].primitiveId]->getMaterial().color;
        mat::Matrix<float, 1, 3> tmp = mixColor(objectColor, lightColor.color, lightColor.intensity);


        tmp *= std::max(0.0f, mat::dotProduct(ray[0].direction, lightColor.direction));

        mat::Matrix<float, 1, 3> specular = {{0, 0, 0}};
        mat::Matrix<float, 1, 3> reflection = mat::normalizeVector(mat::reflectVector(camera.direction, ray[0].direction));
        float specularIntensity = pow(std::max(0.0f, mat::dotProduct(reflection, lightColor.direction)), 32);
        specular = mat::capMatrix(mat::Matrix<float, 1, 3> {{
            specularIntensity, specularIntensity, specularIntensity
        }}, 1.0f);
        tmp += specular;

        finalColor += tmp;
    }
    finalColor = mat::capMatrix(finalColor, 1.0f);
    return finalColor;
}

mat::Matrix<float, 1, 3> Shading::mixColor (mat::Matrix<float, 1, 3> color1, mat::Matrix<float, 1, 3> color2, float ratio)
{
    mat::Matrix<float, 1, 3> finalColor = {{
        color1(0, 0) * (1.0f - ratio) + color2(0, 0) * ratio,
        color1(0, 1) * (1.0f - ratio) + color2(0, 1) * ratio,
        color1(0, 2) * (1.0f - ratio) + color2(0, 2) * ratio
    }};
    return finalColor;
}

mat::Matrix<float, 1, 3> Shading::filterColor (mat::Matrix<float, 1, 3> color, mat::Matrix<float, 1, 3> glassColor)
{
    mat::Matrix<float, 1, 3> finalColor = {{
        color(0, 0) * glassColor(0, 0),
        color(0, 1) * glassColor(0, 1),
        color(0, 2) * glassColor(0, 2)
    }};
    return finalColor;
}


