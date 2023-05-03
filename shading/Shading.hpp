/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** PostProcessing
*/

#pragma once
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "struct.hpp"
#include "Primitives.hpp"
#include "Lights.hpp"

class Shading {
    public:
        ~Shading();
        Shading();
        mat::Matrix<float, 1, 3> shadingPipeline (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, std::vector<normalRay> ray, cameraRay camera, int reflect);
        mat::Matrix<float, 1, 3> shadingPipelineRay (std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray, cameraRay camera, int reflect);
        mat::Matrix<float, 1, 3> mixColor (mat::Matrix<float, 1, 3> color1, mat::Matrix<float, 1, 3> color2, float ratio);
        mat::Matrix<float, 1, 3> filterColor (mat::Matrix<float, 1, 3> color, mat::Matrix<float, 1, 3> glassColor);
        void addReflection (std::vector<normalRay> &intersections, std::vector<IPrimitives*> primitives, std::vector<ILights*> lights, normalRay ray, cameraRay camera, int reflect);
    private:
        mat::Matrix<float, 1, 3> _currentPixelColor;
        mat::Matrix<float, 1, 3> _currentPixelSpecular;
;
};
