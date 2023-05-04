/*
** EPITECH PROJECT, 2023
** square
** File description:
** square
*/

#include "Square.hpp"
#include "Matrix.hpp"

Square::Square(libconfig::Setting &conf)
{
    int px_inf = conf.lookup("x1");
    int py_inf = conf.lookup("y1");
    int pz_inf = conf.lookup("z1");
    int px_sup = conf.lookup("x2");
    int py_sup = conf.lookup("y2");
    int pz_sup = conf.lookup("z2");
    int xr = conf.lookup("xr");
    int yr = conf.lookup("yr");
    int zr = conf.lookup("zr");
    conf.lookupValue("material", _materialName);
    point_inf = {{(float) px_inf, (float) py_inf, (float) pz_inf}};
    point_sup = {{(float) px_sup, (float) py_sup, (float) pz_sup}};
    rotation = {{(float) xr, (float) yr, (float) zr}};
}

Square::~Square()
{
}

std::vector<normalRay> Square::computeIntersection (cameraRay ray)
{
    ray = transformRay(ray, point_inf, rotation);
    std::vector<normalRay> rays;
    mat::Matrix<float, 1, 3> point_inf2 = {{float (0), float (0), float (0)}};
    mat::Matrix<float, 1, 3> point_sup2 = point_sup - point_inf;
    mat::Matrix<float, 1, 3> dist_min;
    mat::Matrix<float, 1, 3> dist_max;
    if (ray.direction(0, 0) == 0 || ray.direction(0, 1) == 0 || ray.direction(0, 2) == 0) {
        return rays;
    }
    float divx = 1 / ray.direction(0, 0);
    if (divx >= 0) {
        dist_min(0, 0) = -(ray.origin(0, 0)) / ray.direction(0, 0);
        dist_max(0, 0) = (point_sup2(0, 0) - ray.origin(0, 0)) / ray.direction(0, 0);
    } else {
        dist_min(0, 0) = (point_sup2(0, 0) - ray.origin(0, 0)) / ray.direction(0, 0);
        dist_max(0, 0) = -(ray.origin(0, 0)) / ray.direction(0, 0);
    }
    float divy = 1 / ray.direction(0, 1);
    if (divy >= 0) {
        dist_min(0, 1) = -ray.origin(0, 1) / ray.direction(0, 1);
        dist_max(0, 1) = (point_sup2(0, 1) - ray.origin(0, 1)) / ray.direction(0, 1);
    } else {
        dist_min(0, 1) = (point_sup2(0, 1) - ray.origin(0, 1)) / ray.direction(0, 1);
        dist_max(0, 1) = -ray.origin(0, 1) / ray.direction(0, 1);
    }

    if ((dist_min(0, 0) > dist_max(0, 1)) || (dist_min(0, 1) > dist_max(0, 0)))
        return rays;

    if (dist_min(0, 1) > dist_min(0, 0))
        dist_min(0, 0) = dist_min(0, 1);

    if (dist_max(0, 1) < dist_max(0, 0))
        dist_max(0, 0) = dist_max(0, 1);

    float divz = 1 / ray.direction(0, 2);
    if (divz >= 0) {
        dist_min(0, 2) = -ray.origin(0, 2) / ray.direction(0, 2);
        dist_max(0, 2) = (point_sup2(0, 2) - ray.origin(0, 2)) / ray.direction(0, 2);
    } else {
        dist_min(0, 2) = (point_sup2(0, 2) - ray.origin(0, 2)) / ray.direction(0, 2);
        dist_max(0, 2) = -ray.origin(0, 2) / ray.direction(0, 2);
    }

    if ((dist_min(0, 0) > dist_max(0, 2)) || (dist_min(0, 2) > dist_max(0, 0)))
        return rays;

    if (dist_min(0, 2) > dist_min(0, 0))
        dist_min(0, 0) = dist_min(0, 2);

    if (dist_max(0, 2) < dist_max(0, 0))
        dist_max(0, 0) = dist_max(0, 2);
    normalRay normal, normal_f;
    normal.origin = {{  ray.origin(0, 0) + (dist_min(0, 0) * ray.direction(0, 0)),
                        ray.origin(0, 1) + (dist_min(0, 1) * ray.direction(0, 1)),
                        ray.origin(0, 2) + (dist_min(0, 2) * ray.direction(0, 2))}};
    normal.origin = {{  ray.origin(0, 0) + (dist_max(0, 0) * ray.direction(0, 0)),
                        ray.origin(0, 1) + (dist_max(0, 1) * ray.direction(0, 1)),
                        ray.origin(0, 2) + (dist_max(0, 2) * ray.direction(0, 2))}};
    normal.direction = {{0, 0, 0}};
    normal.direction = {{0, 0, 0}};
    if (abs(normal.origin(0, 0)) < 0.0001) {
        normal.direction(0, 0) = 1;
    } else if (abs(normal.origin(0, 0) - point_sup2(0, 0)) < 0.0001) {
        normal.direction(0, 0) = -1;
    } else if (abs(normal.origin(0, 1)) < 0.0001) {
        normal.direction(0, 1) = -1;
    } else if (abs(normal.origin(0, 1) - point_sup2(0, 1)) < 0.0001) {
        normal.direction(0, 1) = -1;
    } else if (abs(normal.origin(0, 2)) < 0.0001) {
        normal.direction(0, 2) = 1;
    } else if (abs(normal.origin(0, 2) - point_sup2(0, 2)) < 0.0001) {
        normal.direction(0, 2) = -1;
    }
    if (abs(normal.origin(0, 0)) < 0.0001) {
        normal.direction(0, 0) = -1;
    } else if (abs(normal.origin(0, 0) - point_sup2(0, 0)) < 0.0001) {
        normal.direction(0, 0) = 1;
    } else if (abs(normal.origin(0, 1)) < 0.0001) {
        normal.direction(0, 1) = -1;
    } else if (abs(normal.origin(0, 1) - point_sup2(0, 1)) < 0.0001) {
        normal.direction(0, 1) = 1;
    } else if (abs(normal.origin(0, 2)) < 0.0001) {
        normal.direction(0, 2) = -1;
    } else if (abs(normal.origin(0, 2) - point_sup2(0, 2)) < 0.0001) {
        normal.direction(0, 2) = 1;
    }
    normal = convertHit(normal, point_inf2, rotation);
    normal_f = convertHit(normal_f, point_inf2, rotation);
    rays.push_back(normal);
    rays.push_back(normal_f);
    return rays;
}
