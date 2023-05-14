/*
** EPITECH PROJECT, 2023
** LimitedCone
** File description:
** LimitedCone
*/

#include "LimitedCone.hpp"
#include "Matrix.hpp"

/*
LimitedCone = (
    { t = 20 ; x = 50; y = 20; z = 40; xr = 0; yr = 90; zr = 90; material = "red" } ,
) ;
*/

LimitedCone::LimitedCone(libconfig::Setting &conf)
{
    int xr = conf.lookup("xr");
    int yr = conf.lookup("yr");
    int zr = conf.lookup("zr");
    int x = conf.lookup("x");
    int y = conf.lookup("y");
    int z = conf.lookup("z");
    int t = conf.lookup("t");
    int h = conf.lookup("h");

    theta = float (t);
    height = float (h);
    conf.lookupValue("material", _materialName);
    rotation = {{(float) xr, (float) yr, (float) zr}};
    tip = {{(float) x, (float) y, (float) z}};
}

LimitedCone::~LimitedCone()
{
}

std::vector<normalRay> LimitedCone::computeIntersection(cameraRay ray)
{
    ray = transformRay(ray, tip ,rotation);
    std::vector<normalRay> rays;

    mat::Matrix<float, 1, 3> point = ray.origin;
    float _height = height - ray.origin(0, 1);

    float tan = (theta / height) * (theta / height);

    float a = ray.direction(0, 0) * ray.direction(0, 0) + ray.direction(0, 2) * ray.direction(0, 2) - (tan * (ray.direction(0, 1) *ray.direction(0, 1)));
    float b = 2 * (point(0, 0) * ray.direction(0, 0) + point(0, 2) * ray.direction(0, 2) + tan * _height * ray.direction(0, 1));
    float c = (point(0, 0) * point(0, 0)) + (point(0, 2) * point(0, 2)) - (tan * (_height * _height));

    float delta = pow(b, 2) - 4 * a * c;

    if (abs(delta) < 0.001 || delta < 0)
        return rays;

    float t = (-b - sqrt(delta)) / (2 * a);
    float t2 = (-b + sqrt(delta)) / (2 * a);

    if (t > t2)
        t = t2;

    normalRay normal;
    normal.origin = ray.origin + ray.direction * t;
    if (normal.origin(0, 1) > tip(0, 1) && (normal.origin(0, 1) < tip(0, 1) + height)) {
        normal.direction = mat::normalizeVector(normal.origin);
        if (mat::dotProduct(normal.direction, ray.direction) > 0) {
            normal.direction *= -1;
        }
        normal = convertHit(normal, tip, rotation);
        rays.push_back(normal);
    }
    return rays;
}
