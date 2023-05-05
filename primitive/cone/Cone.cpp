/*
** EPITECH PROJECT, 2023
** cone
** File description:
** cone
*/

#include "Cone.hpp"
#include "Matrix.hpp"

/*
cone = (
    { t = 20 ; x = 50; y = 20; z = 40; xr = 0; yr = 0; zr = 0; material = "red" } ,
) ;
*/

Cone::Cone(libconfig::Setting &conf)
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

Cone::~Cone()
{
}

std::vector<normalRay> Cone::computeIntersection(cameraRay ray)
{
    ray = transformRay(ray, tip ,rotation);
    std::vector<normalRay> rays;

    mat::Matrix<float, 1, 3> V = {{0, 0, -1}};

    float square_tetha = cos(theta) * cos(theta);
    float dpt = mat::dotProduct(ray.direction, V);
    float CV = mat::dotProduct(ray.origin, V);

    float a = dpt * dpt - square_tetha;
    float b = 2 * (dpt * CV - mat::dotProduct(ray.direction, ray.origin) * square_tetha);
    float c = CV * CV - mat::dotProduct(ray.origin, ray.origin) * square_tetha;
    float delta = pow(b, 2) - 4 * a * c;

    if (delta < 0)
        return rays;
    float t1 = (-b - sqrt(delta)) / (2 * a);
    float t2 = (-b + sqrt(delta)) / (2 * a);

    float t = t1;
    if (t < 0. || t2 > 0. && t2 < t)
        t = t2;
    if (t < 0)
        return rays;

    mat::Matrix<float, 1, 3> cp = ray.origin + ray.direction * t;
    float h = mat::dotProduct(cp, V);
    if (h < 0 || h > height)
        return rays;
    normalRay normal;
    normal.origin = cp;
    normal.direction = mat::normalizeVector(cp * mat::dotProduct(V, cp) / mat::dotProduct(cp, cp) - V);
    normal = convertHit(normal, tip, {{0, 0, 0}});
    rays.push_back(normal);
    return rays;
}
