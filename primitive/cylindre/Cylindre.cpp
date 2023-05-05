/*
** EPITECH PROJECT, 2023
** cylindre
** File description:
** cyclindre
*/

#include "Cylindre.hpp"
#include "Matrix.hpp"

Cylindre::Cylindre(libconfig::Setting &conf)
{

    int dist = conf.lookup("val");
    int rayon = conf.lookup("r");
    int xr = conf.lookup("xr");
    int yr = conf.lookup("yr");
    int zr = conf.lookup("zr");
    conf.lookupValue("material", _materialName);
    val = (float) dist;
    r = (float) rayon;
    rotation = {{(float) xr, (float) yr, (float) zr}};
}

Cylindre::~Cylindre()
{
}

std::vector<normalRay> Cylindre::computeIntersection (cameraRay ray)
{
    ray = transformRay(ray, {{0, 0, val}}, rotation);
    std::vector<normalRay> rays;
    std::vector<float> coef = {ray.direction(0, 0) * ray.direction(0, 0) + ray.direction(0, 1) * ray.direction(0, 1),
                             2 * (ray.direction(0, 0) * ray.origin(0, 0) + ray.direction(0, 1) * ray.origin(0, 1)),
                             ray.origin(0, 0) * ray.origin(0, 0) + ray.origin(0, 1) * ray.origin(0, 1) - (r * r)};
    float delta = coef[1] * coef[1] - 4 * coef[0] * coef[2];
    // printf("delta = %f\n", delta);
    if (delta <= 0) {
        // printf("delta <= 0\n");
        return rays;
    }
    float k1 = (-coef[1] - sqrt(delta)) / (2 * coef[0]);
    float k2 = (-coef[1] + sqrt(delta)) / (2 * coef[0]);
    if (k1 > 0) {
        mat::Matrix<float, 1, 3> inter = {{ ray.origin(0, 0) + k1 * ray.direction(0, 0),
                                            ray.origin(0, 1) + k1 * ray.direction(0, 1),
                                            ray.origin(0, 2) + k1 * ray.direction(0, 2)}};
        mat::Matrix<float, 1, 3> inter2 = {{ray.origin(0, 0) + k2 * ray.direction(0, 0),
                                            ray.origin(0, 1) + k2 * ray.direction(0, 1),
                                            ray.origin(0, 2) + k2 * ray.direction(0, 2)}};
        normalRay normal;
        normalRay normal2;
        float normalisation = sqrt(inter(0, 0) * inter(0, 0) + inter(0, 1) * inter(0, 1));
        float normalisation2 = sqrt(inter2(0, 0) * inter2(0, 0) + inter2(0, 1) * inter2(0, 1));
        mat::Matrix<float, 1, 3> vecnormal1 = {{inter(0, 0) / normalisation, inter(0, 1) / normalisation, 0}};
        mat::Matrix<float, 1, 3> vecnormal2 = {{inter2(0, 0) / normalisation2, inter2(0, 1) / normalisation2, 0}};
        normal.origin = inter;
        normal.direction = vecnormal1;
        normal2.origin = inter2;
        normal2.direction = vecnormal2;
        if (mat::dotProduct(normal.direction, ray.direction) > 0)
            normal.direction *= -1;
        if (mat::dotProduct(normal2.direction, ray.direction) > 0)
            normal2.direction *= -1;
        normal = convertHit(normal, {{0, 0, val}}, rotation);
        normal2 = convertHit(normal2, {{0, 0, val}}, rotation);
        rays.push_back(normal);
        rays.push_back(normal2);
    }
    return rays;
}
