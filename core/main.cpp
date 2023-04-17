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

int main(int argc, char *argv[])
{
    if (argc != 2)
        std::exit(84);
    try
    {
        RayTracer::Core core;
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
