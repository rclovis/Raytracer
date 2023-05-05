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
        {x = 0; y = 0; z = 0; xr = 0; yr = 0; zr = 0; material = "green";}
    );
*/

Plane::Plane(libconfig::Setting &conf)
{
    int xr = conf.lookup("xr");
    int yr = conf.lookup("yr");
    int zr = conf.lookup("zr");
    int x = conf.lookup("x");
    int y = conf.lookup("y");
    int z = conf.lookup("z");
    conf.lookupValue("material", _materialName);
    rotation = {{(float) xr, (float) yr, (float) zr}};
    translation = {{(float) x, (float) y, (float) z}};
}

Plane::~Plane()
{
}

std::vector<normalRay> Plane::computeIntersection(cameraRay ray)
{
    ray = transformRay(ray, translation ,rotation);
    std::vector<normalRay> rays;
    float t = (- ray.origin(0,2)) / ray.direction(0,2);
    if (t < 0)
        return rays;
    mat::Matrix<float, 1, 3> p = {{0.0f, 0.0f, 0.0f}};
    p(0, 0) = ray.origin(0,0) + ray.direction(0,0) * t;
    p(0, 1) = ray.origin(0,1) + ray.direction(0,1) * t;
    p(0, 2) = ray.origin(0,2) + ray.direction(0,2) * t;
    normalRay normal;
    normal.origin = p;
    normal.direction = {{0, 0, 1}};
    if (mat::dotProduct(normal.direction, ray.direction) > 0)
        normal.direction *= -1;
    normal = convertHit(normal, translation, rotation);
    rays.push_back(normal);
    return rays;
}
