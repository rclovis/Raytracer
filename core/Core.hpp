/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Core
*/

#pragma once

#include "DynLib.hpp"
#include "Parser.hpp"
#include "Primitives.hpp"

#include <vector>
#include <filesystem>
#include <chrono>
#include <memory>

namespace fs = std::filesystem;

namespace RayTracer
{
    class Core
    {
    public:
        Core();
        ~Core();
        void run();
        mat::Matrix<float, 1, 3> getPixelColor(const std::vector<normalRay> intersections, cameraRay camera);
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
        std::map<std::string, IPostProcessing*> _postProcessing;
        Camera *_camera;
    };
};
