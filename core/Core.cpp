/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Core
*/

#include "Core.hpp"

namespace RayTracer
{
    typedef std::string (*LibType_t)();
    Core::Core()
    {
        std::cout << LOG_CORE("Ready to initialize!");
        std::cout << LOG_CORE("Loading shared libraries...");
        std::map<std::string, DynLib*> primitivesObj;
        std::map<std::string, DynLib*> lightsObj;
        std::map<std::string, DynLib*> postProcessingObj;
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
                    case POSTPROCESSING:
                        postProcessingObj[tmp()] = ptr;
                        break;
                }
            }
        }
        Parser parser;
        parser.setPath("config.cfg");
        _primitives = parser.parsePrimitives(primitivesObj);
        parser.loadMaterials(_primitives);
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
        if (tmp() == "postProcessing") {
            delete ptr;
            return POSTPROCESSING;
        }
        delete ptr;
        return UNKNOWN;
    }

    void Core::run()
    {
        std::vector<std::vector<mat::Matrix<float, 1, 3>>> screen = std::vector<std::vector<mat::Matrix<float, 1, 3>>>(_camera->getHeight(), std::vector<mat::Matrix<float, 1, 3>>(_camera->getWidth(), {{0, 0, 0}}));
        Shading shading;
        // #pragma omp parallel for
        for (int j = _camera->getHeight() - 1; j >= 0; --j) {
            for (int i = 0; i < _camera->getWidth(); ++i) {
                std::vector<normalRay> intersections;
                cameraRay ray = _camera->getRay(i, j);
                int id = 0;
                for (auto &primitive : _primitives) {
                    std::vector<normalRay> intersec = primitive->computeIntersection(ray);
                    for (auto &intersection : intersec) {
                        intersection.primitiveId = id;
                        intersection.distance = _camera->sizeFromIntersection(intersection);
                        intersections.push_back(intersection);
                    }
                    id++;
                }
                std::sort(intersections.begin(), intersections.end(), [](const normalRay &a, const normalRay &b) {
                    return a.distance < b.distance;
                });
                screen[j][i] = shading.shadingPipeline(_primitives, _lights, intersections, ray) * 255;
                // std::cout << screen[j][i] << "\n";
            }
        }

        for (int j = _camera->getHeight() - 1; j >= 0; --j) {
            for (int i = 0; i < _camera->getWidth(); ++i) {
                _camera->getOfs() << (unsigned char)screen[j][i](0, 0) << (unsigned char)screen[j][i](0, 1) << (unsigned char)screen[j][i](0, 2);
            }
        }
    }
};


