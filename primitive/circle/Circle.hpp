/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Circle
*/

#pragma once
#include "Primitives.hpp"
#include <math.h>

extern "C" {
    std::string getType();
    std::string getId();
    IPrimitives *Init(libconfig::Setting &conf);
}

class Circle : public APrimitives{
    public:
        Circle(libconfig::Setting &conf);
        ~Circle();
        void computeIntersection (cameraRay ray);
        mat::Matrix<float, 1, 3> getColor() {return _color;}

    private:
        mat::Matrix<float, 1, 3> _position;
        mat::Matrix<float, 1, 3> _color;
        float _radius;
};

 std::string getType ()
{
    return "primitive";
}

 IPrimitives *Init(libconfig::Setting &conf)
{
    return new Circle(conf);
}

std::string getId ()
{
    return "spheres";
}


