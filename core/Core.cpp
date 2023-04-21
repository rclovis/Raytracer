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
    typedef IPrimitives *(*InitPrimitive_t)(libconfig::Setting &conf);
    Core::Core()
    {
        std::cout << LOG_CORE("Ready to initialize!");
        std::cout << LOG_CORE("Loading shared libraries...");
        fs::path libpath = "lib/";
        std::cout << LOG_CORE("Looking at " << fs::absolute(libpath));
        if (!fs::is_directory(libpath))
            throw LibFolderNotFoundException("Cannot find specified directory");
        if (fs::is_empty(libpath))
            throw NoLibraryFoundException("No shared library where found");
        for (const auto &entry : fs::directory_iterator(libpath))
        {
            if (entry.is_regular_file() &&
                (entry.path().extension().string() == ".so" ||
                 entry.path().extension().string() == ".dylib"))
            {
                std::cout << LOG_CORE("found " << entry.path().filename());
                switch (defineLibType(entry.path()))
                {
                    case PRIMITIVE:
                        DynLib * ptr = new DynLib(entry.path());
                        LibType_t tmp = (LibType_t)ptr->sym("getId");
                        _primitivesObj[tmp()] = ptr;
                        break;
                }
            }
        }
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
        delete ptr;
        return UNKNOWN;
    }

    void Core::run()
    {
        Parser parser;
        parser.setPath("config.cfg");
        // std::vector<IPrimitives*> primitives;
        std::vector<IPrimitives*> primitives = parser.parsePrimitives(_primitivesObj);

        int width = 720;
        int height = 480;
        int fov = 72;

        // create a ppm image
        std::ofstream ofs("./image.ppm", std::ios::out | std::ios::binary);
        ofs << "P6\n" << width << " " << height << "\n255\n";
        // render
        Camera cam(width, height, {{0, 0, -100}}, {{0, 20, 10}}, fov);
        for (int j = height - 1; j >= 0; --j) {
            for (int i = 0; i < width; ++i) {
                cameraRay ray = cam.getRay(i, j);
                mat::Matrix<float, 1, 3> color = {{0.5, 0.5, 0.5}};
                // std::cout << ray.direction << " || ";
                for (auto &primitive : primitives) {
                    primitive->computeIntersection(ray);
                    if (primitive->getIntersection().size() > 0) {
                        color = {{1, 1, 1}};
                        break;
                    }
                }
                ofs << (unsigned char)(color(0, 0) * 255) <<
                    (unsigned char)(color(0, 1) * 255) <<
                    (unsigned char)(color(0, 2) * 255);
            }
        }
    }
};


