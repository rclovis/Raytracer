/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** main
*/

#include "Core.hpp"
#include "logger.hpp"

#include <iostream>
#include <exception>
#include "Camera.hpp"

int main(int argc, char *argv[])
{
    try
    {
        RayTracer::Core core;
        core.run();
    }
    catch (RayTracer::Core::CoreException &e)
    {
        std::cerr << LOG_ERR_CORE(e.what());
        std::exit(84);
    }
    catch (RayTracer::DynLib::DynLibException &e)
    {
        std::cerr << LOG_ERR_DYNLIB(e.what());
        std::exit(84);
    }
}
