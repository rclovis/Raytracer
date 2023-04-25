/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Camera
*/

#include "Camera.hpp"

Camera::Camera(int width, int height, mat::Matrix<float, 1, 3> position, mat::Matrix<float, 1, 3> rotation, int fov)
{
    _width = width;
    _height = height;
    _position = position;
    _fov = fov;
    _rotation = mat::rotationMatrix(rotation(0, 0), rotation(0, 1), rotation(0, 2));
    _ofs << "P6\n" << width << " " << height << "\n255\n";
}

Camera::~Camera()
{
}

cameraRay Camera::getRay(int x, int y)
{
    float fovRad = _fov * (M_PI / 180.0f);

    float size = std::max(_width, _height);
    int offset = std::abs(_width - _height) / 2.0f;
    (_width > _height) ? y += offset : x += offset;
    float ndcX = (2.0f * x) / size - 1.0f;
    float ndcY = (2.0f * y) / size - 1.0f;

    // Calculate direction vector in camera space looking to Y+
    float dirX = ndcX * tan(fovRad / 2.0f);
    float dirY = ndcY * tan(fovRad / 2.0f);
    float dirZ = -1.0f;



    cameraRay ray;
    ray.origin = _position ;
    ray.direction = {{dirX, dirY, dirZ}};
    // ray.direction *= mat::rotationMatrixX(90);
    ray.direction *= mat::rotationMatrix(90, 0, 0);
    ray.direction *= _rotation;
    return ray;
}

float Camera::sizeFromIntersection(normalRay intersection)
{
    mat::Matrix<float, 1, 3> size = intersection.origin - _position;
    return sqrt(pow(size(0, 0), 2) + pow(size(0, 1), 2) + pow(size(0, 2), 2));
}
