/*
** EPITECH PROJECT, 2023
** plane.hpp
** File description:
** planes
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class Plane : public APrimitives{
    public:
        Plane(libconfig::Setting &conf);
        ~Plane();
        std::vector<normalRay> computeIntersection (cameraRay ray);

    private:
        mat::Matrix<float, 1, 3> rotation;
        mat::Matrix<float, 1, 3> translation;
        mat::Matrix<float, 1, 3> normal_vec;
        float _transparency;

};

 std::string getType ()
{
    return "primitive";
}

 IPrimitives *Init(libconfig::Setting &conf)
{
    return new Plane(conf);
}

std::string getId ()
{
    return "plane";
}


