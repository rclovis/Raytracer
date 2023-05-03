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
#include "Matrix.hpp"

int main(int argc, char *argv[])
{

    mat::Matrix<float, 3, 3> mate = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::cout <<  mat::rotationMatrix(45, 0, 0) << std::endl;
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
