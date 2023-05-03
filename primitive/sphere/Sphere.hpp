/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Sphere
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class Sphere : public APrimitives{
    public:
        Sphere(libconfig::Setting &conf);
        ~Sphere();
        std::vector<normalRay> computeIntersection (cameraRay ray);

    private:
        mat::Matrix<float, 1, 3> _position;
        float _radius;
        float _transparency;
};

 std::string getType ()
{
    return "primitive";
}

IPrimitives *Init(libconfig::Setting &conf)
{
    return new Sphere(conf);
}

std::string getId ()
{
    return "spheres";
}


