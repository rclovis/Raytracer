/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Camera
*/

#pragma once
#include "struct.hpp"
#include <math.h>
#include <fstream>

class Camera {
    public:
        Camera(int width, int height, mat::Matrix<float, 1, 3> position, mat::Matrix<float, 1, 3> rotation, int fov);
        ~Camera();
        cameraRay getRay(int x, int y);
        std::ofstream &getOfs() {return _ofs;}
        int getWidth() {return _width;}
        int getHeight() {return _height;}
        float sizeFromIntersection(normalRay intersection);

    private:
        int _width;
        int _height;
        mat::Matrix<float, 1, 3> _position;
        mat::Matrix<float, 3, 3> _rotation;
        int _fov;
        std::ofstream _ofs = std::ofstream("./image.ppm", std::ios::out | std::ios::binary);
};
