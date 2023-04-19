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
    Camera camera(11, 2, {{0, 0, 0}}, {{0, 0, 0}}, 90);

        for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 11; i++) {
            cameraRay ray = camera.getRay(i, j);
            // std::cout << ray.origin<< std::endl;
            std::cout << ray.direction << "\t";
        }
            std::cout<< std::endl;
    }
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
