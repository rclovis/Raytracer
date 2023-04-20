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

    Matrix<float, 1, 3> angleRad = {
        {(float)(rotation(0, 0) * (M_PI / 180.0f)), (float)(rotation(0, 1) * (M_PI / 180.0f)), (float)(rotation(0, 2) * (M_PI / 180.0f))}
    };

    Matrix<float, 3, 3> rotationX = {
        {1, 0, 0},
        {0, cos(angleRad(0, 0)), -sin(angleRad(0, 0))},
        {0, sin(angleRad(0, 0)), cos(angleRad(0, 0))}
    };

    Matrix<float, 3, 3> rotationY = {
        {cos(angleRad(0, 1)), 0, sin(angleRad(0, 1))},
        {0, 1, 0},
        {-sin(angleRad(0, 1)), 0, cos(angleRad(0, 1))}
    };

    Matrix<float, 3, 3> rotationZ = {
        {cos(angleRad(0, 2)), -sin(angleRad(0, 2)), 0},
        {sin(angleRad(0, 2)), cos(angleRad(0, 2)), 0},
        {0, 0, 1}
    };
    _rotation = rotationX * rotationY * rotationZ;
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

    // Calculate direction vector in camera space
    float dirX = ndcX * std::tan(fovRad / 2.0f);
    float dirY = ndcY * std::tan(fovRad / 2.0f);
    float dirZ = 1.0f;
    // Apply rotations in x, y, z axes
    // float cosX = std::cos(_rotation(0, 0) * (M_PI / 180.0f));
    // float sinX = std::sin(_rotation(0, 0) * (M_PI / 180.0f));
    // float cosY = std::cos(_rotation(0, 1) * (M_PI / 180.0f));
    // float sinY = std::sin(_rotation(0, 1) * (M_PI / 180.0f));
    // float cosZ = std::cos(_rotation(0, 2) * (M_PI / 180.0f));
    // float sinZ = std::sin(_rotation(0, 2) * (M_PI / 180.0f));

    // // Rotate around x-axis
    // float tempY = dirY;
    // float tempZ = dirZ;
    // dirY = tempY * cosX + tempZ * sinX;
    // dirZ = -tempY * sinX + tempZ * cosX;

    // // Rotate around y-axis
    // float tempX = dirX;
    // tempZ = dirZ;
    // dirX = tempX * cosY + tempZ * sinY;
    // dirZ = -tempX * sinY + tempZ * cosY;

    // // Rotate around z-axis
    // tempX = dirX;
    // tempY = dirY;
    // dirX = tempX * cosZ - tempY * sinZ;
    // dirY = tempX * sinZ + tempY * cosZ;

    // // Return the final direction vector
    // // return Vec3{dirX, dirY, dirZ};

    cameraRay ray;
    ray.origin = _position;
    ray.direction = {{dirX, dirY, dirZ}};
    ray.direction = ray.direction * _rotation;
    return ray;

}

