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
    IPrimitives *Init();
}

class Circle : public APrimitives{
    public:
        Circle(Matrix<float, 1, 3> position, float radius);
        ~Circle();
        void computeIntersection (cameraRay ray);

    private:
        Matrix<float, 1, 3> _position;
        float _radius;
};

 std::string getType ()
{
    return "primitive";
}

 IPrimitives *Init()
{
    return new Circle({{0, 0, 1000}}, 5);
}


