/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Parser
*/

#pragma once
#include <string>
#include <vector>
#include <libconfig.h++>
#include "Primitives.hpp"
#include "Lights.hpp"

class Parser {
    public:
        Parser();
        ~Parser();
        void setPath(std::string path);
        std::vector<IPrimitives *> parsePrimitives();
        std::vector<ILights *> parseLights();

    private:
        std::string _path;
};
