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
#include "Camera.hpp"
#include "logger.hpp"
#include <memory>
#include "DynLib.hpp"

class Parser {
    public:
        typedef IPrimitives *(*InitPrimitive_t)(libconfig::Setting &conf);
        typedef ILights *(*InitLights_t)(libconfig::Setting &conf);

        Parser();
        ~Parser();
        void setPath(std::string path);
        std::vector<IPrimitives *> parsePrimitives(std::map<std::string, RayTracer::DynLib*> primitivesObj);
        std::vector<ILights *> parseLights(std::map<std::string, RayTracer::DynLib*> primitivesObj);
        void loadMaterials(std::vector<IPrimitives *> primitives);
        bool antiAliasing();
        Camera *parseCamera();

    private:
        std::string _path;
};
