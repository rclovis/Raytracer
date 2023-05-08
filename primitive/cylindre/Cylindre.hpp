/*
** EPITECH PROJECT, 2023
** cylindre.hpp
** File description:
** cylindre
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class Cylindre : public APrimitives{
    public:
        Cylindre(libconfig::Setting &conf);
        ~Cylindre();
        std::vector<normalRay> computeIntersection (cameraRay ray);

    private:
    float val;
    float r;
    mat::Matrix<float, 1, 3> rotation;
    float _transparency;
};

 std::string getType ()
{
    return "primitive";
}

 IPrimitives *Init(libconfig::Setting &conf)
{
    return new Cylindre(conf);
}

std::string getId ()
{
    return "cylindre";
}
