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

mat::Matrix<float, 1, 3> Shading::shadingPipelineRay (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray, cameraRay camera, int reflect)
{
    mat::Matrix<float, 1, 3> finalColor = {{0, 0, 0}};
    mat::Matrix<float, 1, 3> ambientColor = {{0, 0, 0}};
    float ambientIntensity = 0;
    mat::Matrix<float, 1, 3> specular = {{0, 0, 0}};

    for (auto &light : lights) {
        //recupérer le rayon de lumière (contient la direction et la couleur)
        lightColor lightColor = light->getLight(ray);
        if (lightColor.ambient == true) {
            ambientColor = mixColor(ambientColor, lightColor.color, lightColor.intensity);
            ambientIntensity += lightColor.intensity;
        }
        //

        //calculer l'intersection entre le rayon de lumière et les primitives (si l'endroit touché est dans l'ombre, ou pas)
        cameraRay lightRay;
        lightRay.origin = ray.origin + ray.direction * 0.01;
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
        ////transparence des ombres
        float opacity = 0;
        for (auto &intersection : intersections) {
            opacity += primitives[intersection.primitiveId]->getMaterial().transparency * (1 - opacity);
            if (opacity >= 1) {
                opacity = 1;
                break;
            }
            lightColor.color = mixColor(lightColor.color, primitives[intersection.primitiveId]->getMaterial().color, 1 - primitives[intersection.primitiveId]->getMaterial().transparency);
        }
        if (opacity == 1) {
            continue;
        }
        ////
        //

        mat::Matrix<float, 1, 3> objectColor = primitives[ray.primitiveId]->getMaterial().color;
        finalColor = mixColor(objectColor, lightColor.color, lightColor.intensity) * lightColor.intensity * primitives[ray.primitiveId]->getMaterial().transparency;
        finalColor *= std::max(0.0f, mat::dotProduct(ray.direction, lightColor.direction));


        mat::Matrix<float, 1, 3> reflection = mat::normalizeVector(mat::reflectVector(camera.direction, ray.direction));
        float specularIntensity = pow(std::max(0.0f, mat::dotProduct(reflection, lightColor.direction)), 100);
        specular += mat::capMatrix(mat::Matrix<float, 1, 3> {{
            specularIntensity, specularIntensity, specularIntensity
        }}, 1.0f);
    }
    finalColor += mixColor(ambientColor, primitives[ray.primitiveId]->getMaterial().color, ambientIntensity * primitives[ray.primitiveId]->getMaterial().transparency);


    cameraRay reflectionRay;
    reflectionRay.origin = ray.origin + ray.direction * 0.01;
    reflectionRay.direction = mat::reflectVector(mat::normalizeVector(camera.direction), ray.direction);
    if (primitives[ray.primitiveId]->getMaterial().reflection != 0 && reflect > 0) {
        std::vector<normalRay> intersections;
        int id = 0;
        for (auto &primitive : primitives) {
            std::vector<normalRay> intersec = primitive->computeIntersection(reflectionRay);
            for (auto &intersection : intersec) {
                intersection.primitiveId = id;
                intersection.distance = sqrt(pow(intersection.origin(0, 0) - reflectionRay.origin(0, 0), 2) + pow(intersection.origin(0, 1) - reflectionRay.origin(0, 1), 2) + pow(intersection.origin(0, 2) - reflectionRay.origin(0, 2), 2));
                intersections.push_back(intersection);
            }
            id++;
        }
        std::sort(intersections.begin(), intersections.end(), [](const normalRay &a, const normalRay &b) {
            return a.distance < b.distance;
        });
        finalColor = mixColor(finalColor, shadingPipeline(primitives, lights, intersections, reflectionRay, reflect - 1), primitives[ray.primitiveId]->getMaterial().reflection);
    }
    finalColor += specular;
    finalColor = mat::capMatrix(finalColor, 1.0f);
    return finalColor;
}

mat::Matrix<float, 1, 3> Shading::shadingPipeline (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, std::vector<normalRay> ray, cameraRay camera, int reflect)
{
    mat::Matrix<float, 1, 3> finalColor = {{0, 0, 0}};
    if (ray.size() == 0) return finalColor;
    finalColor = {{0, 0, 0}};
    float opacity = 0;
    float mixValue = 1;
    int t = 0;
    for (auto &r : ray) {
        if (t == 0) {
            finalColor = shadingPipelineRay(primitives, lights, r, camera, reflect);
        } else {
            finalColor = mixColor(finalColor, shadingPipelineRay(primitives, lights, r, camera, reflect), 1 - opacity);
        }
        opacity += (primitives[r.primitiveId]->getMaterial().transparency + primitives[r.primitiveId]->getMaterial().reflection) * (1 - opacity);
        if (opacity >= 1) break;
        t++;
    }
    return mat::capMatrix(finalColor, 1.0f);
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


