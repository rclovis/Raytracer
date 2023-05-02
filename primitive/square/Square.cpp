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
    std::cerr << _materialName << "\n";
    point_inf = {{(float) px_inf, (float) py_inf, (float) pz_inf}};
    point_sup = {{(float) px_sup, (float) py_sup, (float) pz_sup}};
    rotation = {{(float) xr, (float) yr, (float) zr}};
    std::cerr << rotation(0,0) << "\n";
    std::cerr << rotation(0,1) << "\n";
    std::cerr << rotation(0,2) << "\n";
}

Square::~Square()
{
}

std::vector<normalRay> Square::computeIntersection (cameraRay ray)
{
    ray = transformRay(ray, point_inf, rotation);
    std::vector<normalRay> rays;
    point_sup -= point_inf;
    point_inf = {{float (0), float (0), float (0)}};
    mat::Matrix<float, 1, 3> dist_min;
    mat::Matrix<float, 1, 3> dist_max;
    if (ray.direction(0,0) >= 0) {
        dist_min(0, 0) = -ray.origin(0, 0) / ray.direction(0, 0);
        dist_max(0, 0) = (point_sup(0, 0) - ray.origin(0, 0)) / ray.direction(0, 0);
    } else {
        dist_min(0, 0) = (point_sup(0, 0) - ray.origin(0, 0)) / ray.direction(0, 0);
        dist_max(0, 0) = -ray.origin(0, 0) / ray.direction(0, 0);
    }

    if (ray.direction(0,1) >= 0) {
        dist_min(0, 1) = -ray.origin(0, 1) / ray.direction(0, 1);
        dist_max(0, 1) = (point_sup(0, 1) - ray.origin(0, 1)) / ray.direction(0, 1);
    } else {
        dist_min(0, 1) = (point_sup(0, 1) - ray.origin(0, 1)) / ray.direction(0, 1);
        dist_max(0, 1) = -ray.origin(0, 1) / ray.direction(0, 1);
    }


    if ((dist_min(0, 0) > dist_max(0, 1)) || (dist_min(0, 1) > dist_max(0, 0)))
        return rays;

    if (dist_min(0, 1) > dist_min(0, 0))
        dist_min(0, 0) = dist_min(0, 1);

    if (dist_max(0, 1) < dist_max(0, 0))
        dist_max(0, 0) = dist_max(0, 1);

    if (ray.direction(0,2) >= 0) {
        dist_min(0, 2) = -ray.origin(0, 2) / ray.direction(0, 2);
        dist_max(0, 2) = (point_sup(0, 2) - ray.origin(0, 2)) / ray.direction(0, 2);
    } else {
        dist_min(0, 2) = (point_sup(0, 2) - ray.origin(0, 2)) / ray.direction(0, 2);
        dist_max(0, 2) = -ray.origin(0, 2) / ray.direction(0, 2);
    }

    if ((dist_min(0, 0) > dist_max(0, 2)) || (dist_min(0, 2) > dist_max(0, 0)))
        return rays;

    if (dist_min(0, 2) > dist_min(0, 0))
        dist_min(0, 0) = dist_min(0, 2);

    if (dist_max(0, 2) < dist_max(0, 0))
        dist_max(0, 0) = dist_max(0, 2);
    normalRay normal;
    normal.origin = {{ray.origin(0, 0) + (dist_min(0, 0) * ray.direction(0, 0)),
                    ray.origin(0, 1) + (dist_min(0, 1) * ray.direction(0, 1)),
                    ray.origin(0, 2) + (dist_min(0, 2) * ray.direction(0, 2))}};
    normal.direction = mat::normalizeVector(normal.origin);
    normal = convertHit(normal, point_inf, rotation);
    rays.push_back(normal);
}
