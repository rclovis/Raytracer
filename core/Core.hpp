/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Core
*/

#pragma once

#include "DynLib.hpp"
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
            LIGHT,
        };

        enum Core::_libType defineLibType(const fs::path &libpath);
        std::vector<std::unique_ptr<DynLib>> _primitiveLibs;

    };
};
