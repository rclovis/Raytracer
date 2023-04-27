/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Core
*/

#pragma once

#include "DynLib.hpp"
#include "Parser.hpp"
#include "logger.hpp"
#include "Camera.hpp"
#include "Primitives.hpp"
#include "Shading.hpp"
#include <vector>
#include <filesystem>
#include <chrono>
#include <memory>
#include <iostream>
#include <exception>
#include <fstream>
#include <algorithm>
#include <cmath>

namespace fs = std::filesystem;

namespace RayTracer
{
    class Core
    {
    public:
        Core();
        ~Core();
        void run();
        class CoreException : public std::runtime_error
        {
            using std::runtime_error::runtime_error;
        };

    private:
        class LibFolderNotFoundException : public CoreException
        {
            using CoreException::CoreException;
        };
        class NoLibraryFoundException : public CoreException
        {
            using CoreException::CoreException;
        };

        enum _libType
        {
            UNKNOWN,
            PRIMITIVE,
            POSTPROCESSING,
            LIGHT,
        };

        enum Core::_libType defineLibType(const fs::path &libpath);
        std::vector<IPrimitives*> _primitives;
        std::vector<ILights*> _lights;
        Camera *_camera;
    };
};
