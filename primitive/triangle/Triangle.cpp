/*
** EPITECH PROJECT, 2023
** Triangle
** File description:
** Triangle
*/

#include "Triangle.hpp"
#include "Matrix.hpp"

/*
    Triangle = (
        { a = -20; b = 0; c = 80; d = 20; e = 20; f = 80; g = 0; h = 20; i = 20; xr = 0; yr = 0; zr = 0; material = "green"; } ,
    );
*/

Triangle::Triangle(libconfig::Setting &conf)
{
    int a = conf.lookup("a");
    int b = conf.lookup("b");
    int c = conf.lookup("c");
    int d = conf.lookup("d");
    int e = conf.lookup("e");
    int f = conf.lookup("f");
    int g = conf.lookup("g");
    int h = conf.lookup("h");
    int i = conf.lookup("i");
    int xr = conf.lookup("xr");
    int yr = conf.lookup("yr");
    int zr = conf.lookup("zr");

    conf.lookupValue("material", _materialName);
    rotation = {{(float) xr, (float) yr, (float) zr}};
    point_a = {{(float) a, (float) b, (float) c}};
    point_b = {{(float) d, (float) e, (float) f}};
    point_c = {{(float) g, (float) h, (float) i}};

    mat::Matrix<float, 1, 3> U = point_b - point_a;
    mat::Matrix<float, 1, 3> V = point_c - point_a;

    _normal = mat::normalizeVector(mat::crossProduct(U, V));
}

Triangle::~Triangle()
{
}

std::vector<normalRay> Triangle::computeIntersection(cameraRay ray)
{
    std::vector<normalRay> rays;
    float D = - (mat::dotProduct(_normal, point_a));
    if (abs(D) <= 1e-6) // maybe just D == 0
        return rays;
    if (mat::dotProduct(_normal, ray.direction) == 0)
        return rays;
    float t = (- (mat::dotProduct(_normal, ray.origin) + D)) / mat::dotProduct(_normal, ray.direction);
    if (t < 0)
        return rays;
    mat::Matrix<float, 1, 3> inter = {{ray.origin(0, 0) + (ray.direction(0, 0) * t), ray.origin(0, 1) + (ray.direction(0, 1) * t), ray.origin(0, 2) + (ray.direction(0, 2) * t)}};

    mat::Matrix<float, 1, 3> edge0 = point_b - point_a;
    mat::Matrix<float, 1, 3> vp0 = inter - point_a;
    mat::Matrix<float, 1, 3> C = mat::crossProduct(edge0, vp0);
    if (mat::dotProduct(_normal, C) < 0) return rays;

    mat::Matrix<float, 1, 3> edge1 = point_c - point_b;
    mat::Matrix<float, 1, 3> vp1 = inter - point_b;
    C = mat::crossProduct(edge1, vp1);
    if (mat::dotProduct(_normal, C) < 0) return rays;

    mat::Matrix<float, 1, 3> edge2 = point_a - point_c;
    mat::Matrix<float, 1, 3> vp2 = inter - point_c;
    C = mat::crossProduct(edge2, vp2);
    if (mat::dotProduct(_normal, C) < 0) return rays;

    normalRay normal;
    normal.origin = inter;
    normal.direction = _normal;
    if (mat::dotProduct(_normal, ray.direction) < 0)
        normal.direction *= -1;
    rays.push_back(normal);
    return rays;
}
