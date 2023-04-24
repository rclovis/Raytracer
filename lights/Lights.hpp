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
#include "Primitives.hpp"

class ILights {
    public:
        virtual ~ILights() = default;
        virtual lightColor getLight(normalRay ray) = 0;
};
