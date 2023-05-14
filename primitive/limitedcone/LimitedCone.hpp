/*
** EPITECH PROJECT, 2023
** LimitedCone.hpp
** File description:
** LimitedCones
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class LimitedCone : public APrimitives{
    public:
        LimitedCone(libconfig::Setting &conf);
        ~LimitedCone();
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
    return new LimitedCone(conf);
}

std::string getId ()
{
    return "limitedcone";
}


