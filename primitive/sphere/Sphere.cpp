/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Sphere
*/

#include "Sphere.hpp"

/*
spheres = (
    { x = 60; y = 5; z = 40; rad = 25; color = { r = 255; g = 64; b = 64; }; } ,
    { x = -40; y = 20; z = -10; rad = 35; color = { r = 64; g = 255; b = 64; }; }
) ;
*/

Sphere::Sphere(libconfig::Setting &conf)
{
    int x = conf.lookup("x");
    int y = conf.lookup("y");
    int z = conf.lookup("z");
    int rad = conf.lookup("rad");
    conf.lookupValue("material", _materialName);
    _position = {{(float)x, (float)y, (float)z}};
    _radius = (float)rad;
}

Sphere::~Sphere()
{
}

std::vector<normalRay> Sphere::computeIntersection (cameraRay ray)
{
    ray = transformRay(ray, _position, {{0, 0, 0}});
    std::vector<normalRay> rays;
    float a = pow(ray.direction(0, 0), 2) + pow(ray.direction(0, 1), 2) + pow(ray.direction(0, 2), 2);
    float b = 2 * ray.direction(0, 0) * ray.origin(0, 0) + 2 * ray.direction(0, 1) * ray.origin(0, 1) + 2 * ray.direction(0, 2) * ray.origin(0, 2);
    float c = pow(ray.origin(0, 0), 2) + pow(ray.origin(0, 1), 2) + pow(ray.origin(0, 2), 2) - pow(_radius, 2);
    float delta = pow(b, 2) - 4 * a * c;
    if (delta < 0)
        return rays;
    if (delta == 0) {
        float t = -b / (2 * a);
        normalRay normal;
        normal.origin = {{ray.origin(0, 0) + t * ray.direction(0, 0), ray.origin(0, 1) + t * ray.direction(0, 1), ray.origin(0, 2) + t * ray.direction(0, 2)}};
        normal.direction = mat::normalizeVector(normal.origin);
        if (mat::dotProduct(normal.direction, ray.direction) > 0) {
            normal.direction *= -1;
        }
        normal = convertHit(normal, _position, {{0, 0, 0}});
        rays.push_back(normal);
        return rays;
    }
    float t1 = (-b + sqrt(delta)) / (2 * a);
    float t2 = (-b - sqrt(delta)) / (2 * a);
    if (t1 > 0) {
        normalRay normal;
        normal.origin = {{ray.origin(0, 0) + t1 * ray.direction(0, 0), ray.origin(0, 1) + t1 * ray.direction(0, 1), ray.origin(0, 2) + t1 * ray.direction(0, 2)}};
        normal.direction = mat::normalizeVector(normal.origin);
        if (mat::dotProduct(normal.direction, ray.direction) > 0) {
            normal.direction *= -1;
        }
        normal = convertHit(normal, _position, {{0, 0, 0}});
        rays.push_back(normal);
    }
    if (t2 > 0) {
        normalRay normal;
        normal.origin = {{ray.origin(0, 0) + t2 * ray.direction(0, 0), ray.origin(0, 1) + t2 * ray.direction(0, 1), ray.origin(0, 2) + t2 * ray.direction(0, 2)}};
        normal.direction = mat::normalizeVector(normal.origin);
        if (mat::dotProduct(normal.direction, ray.direction) > 0) {
            normal.direction *= -1;
        }
        normal = convertHit(normal, _position, {{0, 0, 0}});
        rays.push_back(normal);
    }
    return rays;
}

