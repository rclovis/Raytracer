/*
** EPITECH PROJECT, 2023
** square.hpp
** File description:
** square
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class Square : public APrimitives{
    public:
        Square(libconfig::Setting &conf);
        ~Square();
        std::vector<normalRay> computeIntersection (cameraRay ray);

    private:
    float d;
    mat::Matrix<float, 1, 3> rotation;
    mat::Matrix<float, 1, 3> point_inf;
    mat::Matrix<float, 1, 3> point_sup;
    float _transparency;
};

 std::string getType ()
{
    return "primitive";
}

 IPrimitives *Init(libconfig::Setting &conf)
{
    return new Square(conf);
}

std::string getId ()
{
    return "square";
}
