/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Obj
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>
#include <sstream>
#include <fstream>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class Obj : public APrimitives{
    public:
        Obj(libconfig::Setting &conf);
        ~Obj();
        void loadObj (std::string fileName);
        std::vector<normalRay> computeIntersection (cameraRay ray);

    private:
        std::vector<mat::Matrix<float, 1, 3>> _vertices;
        mat::Matrix<float, 1, 3> _position;
        mat::Matrix<float, 1, 3> _rotation;
};

 std::string getType ()
{
    return "primitive";
}

IPrimitives *Init(libconfig::Setting &conf)
{
    return new Obj(conf);
}

std::string getId ()
{
    return "obj";
}
