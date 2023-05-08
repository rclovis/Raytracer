/*
** EPITECH PROJECT, 2023
** plane
** File description:
** plane
*/

#include "Plane.hpp"
#include "Matrix.hpp"

/*
plane = (
    { a = 20; b = 5; c = 3; d = 40; e = 5; f = 20; x = 60; y = 5; z = 40; color = { r = 255; g = 64; b = 64; }; } ,
) ;
*/

Plane::Plane(libconfig::Setting &conf)
{
    int x = conf.lookup("x");
    int y = conf.lookup("y");
    int z = conf.lookup("z");
    int xr = conf.lookup("xr");
    int yr = conf.lookup("yr");
    int zr = conf.lookup("zr");
    conf.lookupValue("material", _materialName);
    rotation = {{(float) xr, (float) yr, (float) zr}};
    translation = {{(float) x, (float) y, (float) z}};
    std::cout << rotation << std::endl;
    std::cout << translation << std::endl;
}

Plane::~Plane()
{
}

std::vector<normalRay> Plane::computeIntersection(cameraRay ray)
{
    ray = transformRay(ray, translation, rotation);
    std::vector<normalRay> rays;
    float t = (- ray.origin(0,2)) / ray.direction(0,2);
    if (t < 0)
        return rays;
    float x = ray.origin(0,0) + ray.direction(0,0) * t;
    float y = ray.origin(0,1) + ray.direction(0,1) * t;
    float z = ray.origin(0,2) + ray.direction(0,2) * t;
    normalRay normal;
    normal.origin = {{x, y, z}};
    normal.direction = {{0, 0, 1}};
    if (mat::dotProduct(normal.direction, ray.direction) < 0)
        normal.direction *= -1;
    normal = convertHit(normal, translation, rotation);
    rays.push_back(normal);
    return rays;
}
