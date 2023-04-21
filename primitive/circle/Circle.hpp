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
    IPrimitives *Init(std::string conf);
}

class Circle : public APrimitives{
    public:
        Circle(std::string conf);
        ~Circle();
        void computeIntersection (cameraRay ray);

    private:
        mat::Matrix<float, 1, 3> _position;
        float _radius;
};

 std::string getType ()
{
    return "primitive";
}

 IPrimitives *Init(std::string conf)
{
    return new Circle(conf);
}

std::string getId ()
{
    return "circle";
}


