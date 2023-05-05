/*
** EPITECH PROJECT, 2023
** cone.hpp
** File description:
** cones
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class Cone : public APrimitives{
    public:
        Cone(libconfig::Setting &conf);
        ~Cone();
        std::vector<normalRay> computeIntersection (cameraRay ray);

    private:
        mat::Matrix<float, 1, 3> rotation;
        mat::Matrix<float, 1, 3> tip;
        float theta;
        float height;
        float _transparency;
};

 std::string getType ()
{
    return "primitive";
}

 IPrimitives *Init(libconfig::Setting &conf)
{
    return new Cone(conf);
}

std::string getId ()
{
    return "cone";
}


