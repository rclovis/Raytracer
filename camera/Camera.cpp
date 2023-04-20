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

    _rotation = rotation;
}

Camera::~Camera()
{
}

cameraRay Camera::getRay(int x, int y)
{
    // cameraRay ray;
    // int fov = 90;
    // ray.origin = _position;
    // float ndcX = (x + 0.5f) / _width * 2.0f - 1.0f;
    // float ndcY = (y + 0.5f) / _height * 2.0f - 1.0f;

    // float fovScale = tan(_fov * 0.5f * M_PI / 180.0f);
    // ray.direction = {{ndcX * fovScale, ndcY * fovScale, 1.0f}};


    // ray.direction = ray.direction * _rotation;
    // return ray;

    // Convert field of view from degrees to radians
    float fovRad = _fov * (M_PI / 180.0f);

    // Calculate normalized device coordinates (NDC) from pixel coordinates
    float ndcX = (2.0f * x) / _width - 1.0f;
    float ndcY = 1.0f - (2.0f * y) / _height;

    // Calculate direction vector in camera space
    float dirX = ndcX * std::tan(fovRad * 0.5f);
    float dirY = ndcY * std::tan(fovRad * 0.5f);
    float dirZ = -1.0f;

    // Apply rotations in x, y, z axes
    float cosX = std::cos(_rotation(0, 0) * (M_PI / 180.0f));
    float sinX = std::sin(_rotation(0, 0) * (M_PI / 180.0f));
    float cosY = std::cos(_rotation(0, 1) * (M_PI / 180.0f));
    float sinY = std::sin(_rotation(0, 1) * (M_PI / 180.0f));
    float cosZ = std::cos(_rotation(0, 2) * (M_PI / 180.0f));
    float sinZ = std::sin(_rotation(0, 2) * (M_PI / 180.0f));

    // Rotate around x-axis
    float tempY = dirY;
    float tempZ = dirZ;
    dirY = tempY * cosX + tempZ * sinX;
    dirZ = -tempY * sinX + tempZ * cosX;

    // Rotate around y-axis
    float tempX = dirX;
    tempZ = dirZ;
    dirX = tempX * cosY + tempZ * sinY;
    dirZ = -tempX * sinY + tempZ * cosY;

    // Rotate around z-axis
    tempX = dirX;
    tempY = dirY;
    dirX = tempX * cosZ - tempY * sinZ;
    dirY = tempX * sinZ + tempY * cosZ;

    // Return the final direction vector
    // return Vec3{dirX, dirY, dirZ};

    cameraRay ray;
    ray.origin = _position;
    ray.direction = {{dirX, dirY, dirZ}};
    return ray;

}

