/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Core
*/

#include "Core.hpp"
#include "logger.hpp"
#include "Primitives.hpp"
#include <iostream>
#include <exception>

namespace RayTracer
{
    typedef std::string (*LibType_t)();

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
                    _primitiveLibs.emplace_back(new DynLib(entry.path()));
                    break;
                default:
                    std::cerr << LOG_CORE("unknown library type");
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
};
