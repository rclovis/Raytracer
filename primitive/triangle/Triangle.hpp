/*
** EPITECH PROJECT, 2023
** Triangle.hpp
** File description:
** Triangles
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class Triangle : public APrimitives{
    public:
        Triangle(libconfig::Setting &conf);
        ~Triangle();
        std::vector<normalRay> computeIntersection (cameraRay ray);

    private:
        mat::Matrix<float, 1, 3> rotation;
        mat::Matrix<float, 1, 3> _normal;
        mat::Matrix<float, 1, 3> point_a;
        mat::Matrix<float, 1, 3> point_b;
        mat::Matrix<float, 1, 3> point_c;
        float _transparency;

};

 std::string getType ()
{
    return "primitive";
}

 IPrimitives *Init(libconfig::Setting &conf)
{
    return new Triangle(conf);
}

std::string getId ()
{
    return "triangle";
}


