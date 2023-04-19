/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Camera
*/

#include "Camera.hpp"

Camera::Camera(int width, int height, Matrix<float, 1, 3> position, Matrix<float, 1, 3> rotation, int fov)
{
    _width = width;
    _height = height;
    _position = position;
    _fov = fov;

    _rotation = {
        {cos(rotation(0, 0)) * cos(rotation(0, 2)), cos(rotation(0, 0)) * sin(rotation(0, 2)), -sin(rotation(0, 0))},
        {sin(rotation(0, 1)) * sin(rotation(0, 0)) * cos(rotation(0, 2)) - cos(rotation(0, 1)) * sin(rotation(0, 2)), sin(rotation(0, 1)) * sin(rotation(0, 0)) * sin(rotation(0, 2)) + cos(rotation(0, 1)) * cos(rotation(0, 2)), sin(rotation(0, 1)) * cos(rotation(0, 0))},
        {cos(rotation(0, 1)) * sin(rotation(0, 0)) * cos(rotation(0, 2)) + sin(rotation(0, 1)) * sin(rotation(0, 2)), cos(rotation(0, 1)) * sin(rotation(0, 0)) * sin(rotation(0, 2)) - sin(rotation(0, 1)) * cos(rotation(0, 2)), cos(rotation(0, 1)) * cos(rotation(0, 0))}
    };
}

Camera::~Camera()
{
}

cameraRay Camera::getRay(int x, int y)
{
    cameraRay ray;
    int fov = 90;
    ray.origin = _position;
    float ndcX = (x + 0.5f) / _width * 2.0f - 1.0f;
    float ndcY = (y + 0.5f) / _height * 2.0f - 1.0f;

    float fovScale = tan(_fov * 0.5f * M_PI / 180.0f);
    ray.direction = {{ndcX * fovScale, ndcY * fovScale, 1.0f}};


    ray.direction = ray.direction * _rotation;
    return ray;
}
