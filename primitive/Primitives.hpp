/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Primitives
*/

#pragma once
#include <vector>
#include <map>
#include <string>
#include "struct.hpp"

class IPrimitives {
    public:
        virtual ~IPrimitives() = default;
        virtual void computeIntersection (cameraRay ray) = 0;
        virtual std::vector<normalRay> getIntersection () = 0;
};

class APrimitives : public IPrimitives {
    public:
        std::vector<normalRay> getIntersection () {return _ray;}
    protected:
        std::vector<normalRay> _ray;
};
