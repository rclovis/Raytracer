/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Core
*/

#include "Core.hpp"
#include "logger.hpp"
#include "Primitives.hpp"
#include "Camera.hpp"
#include <iostream>
#include <exception>
#include <fstream>
#include <algorithm>
#include <cmath>

namespace RayTracer
{
    typedef std::string (*LibType_t)();
    Core::Core()
    {
        std::cout << LOG_CORE("Ready to initialize!");
        std::cout << LOG_CORE("Loading shared libraries...");
        std::map<std::string, DynLib*> primitivesObj;
        std::map<std::string, DynLib*> lightsObj;
        fs::path libpath = "lib/";
        std::cout << LOG_CORE("Looking at " << fs::absolute(libpath));
        if (!fs::is_directory(libpath))
            throw LibFolderNotFoundException("Cannot find specified directory");
        if (fs::is_empty(libpath))
            throw NoLibraryFoundException("No shared library where found");
        for (const auto &entry : fs::directory_iterator(libpath)) {
            if (entry.is_regular_file() && (entry.path().extension().string() == ".so" || entry.path().extension().string() == ".dylib")) {
                std::cout << LOG_CORE("found " << entry.path().filename());
                DynLib * ptr = new DynLib(entry.path());
                LibType_t tmp = (LibType_t)ptr->sym("getId");
                switch (defineLibType(entry.path())) {
                    case PRIMITIVE:
                        primitivesObj[tmp()] = ptr;
                        break;
                    case LIGHT:
                        lightsObj[tmp()] = ptr;
                        break;
                }
            }
        }
        Parser parser;
        parser.setPath("config.cfg");
        _primitives = parser.parsePrimitives(primitivesObj);
        _lights = parser.parseLights(lightsObj);
        _camera = parser.parseCamera();
    }

    Core::~Core()
    {
        std::cout << LOG_CORE("Core moving out!");
    }

    enum Core::_libType Core::defineLibType(const fs::path &libpath)
    {
        DynLib * ptr = new DynLib("lib/" + libpath.filename().string());
        LibType_t tmp = (LibType_t)ptr->sym("getType");

        if (tmp() == "primitive") {
            delete ptr;
            return PRIMITIVE;
        }
        if (tmp() == "light") {
            delete ptr;
            return LIGHT;
        }
        delete ptr;
        return UNKNOWN;
    }

    void Core::run()
    {
        std::vector<normalRay> intersections;
        for (int j = _camera->getHeight() - 1; j >= 0; --j) {
            for (int i = 0; i < _camera->getWidth(); ++i) {
                intersections.clear();
                cameraRay ray = _camera->getRay(i, j);
                mat::Matrix<float, 1, 3> color = {{0.5, 0.5, 0.5}};
                for (auto &primitive : _primitives) {
                    primitive->computeIntersection(ray);
                    for (auto &intersection : primitive->getIntersection()) {
                        intersection.distance = _camera->sizeFromIntersection(intersection);
                        intersections.push_back(intersection);
                    }
                }
                std::sort(intersections.begin(), intersections.end(), [](const normalRay &a, const normalRay &b) {
                    return a.distance < b.distance;
                });
                _camera->getOfs() << (unsigned char)(color(0, 0) * 255) <<
                    (unsigned char)(color(0, 1) * 255) <<
                    (unsigned char)(color(0, 2) * 255);
            }
        }
    }
};


