/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Camera
*/

#pragma once
#include "struct.hpp"
#include <math.h>

class Camera {
    public:
        Camera(int width, int height, Matrix<float, 1, 3> position, Matrix<float, 1, 3> rotation, int fov);
        ~Camera();
        cameraRay getRay(int x, int y);

    private:
        int _width;
        int _height;
        Matrix<float, 1, 3> _position;
        Matrix<float, 1, 3> _rotation;
        int _fov;
};
