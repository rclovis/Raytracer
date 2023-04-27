/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** struct
*/

#pragma once
#include "Matrix.hpp"

struct normalRay {
    mat::Matrix<float, 1, 3> origin;
    mat::Matrix<float, 1, 3> direction;
    mat::Matrix<float, 1, 2> uv;
    int primitiveId;
    float distance;
} typedef normalRay;

struct cameraRay {
    mat::Matrix<float, 1, 3> origin;
    mat::Matrix<float, 1, 3> direction;
} typedef cameraRay;

struct pixelColor {
    mat::Matrix<float, 1, 3> color;
} typedef pixelColor;

struct lightColor {
    mat::Matrix<float, 1, 3> color;
    mat::Matrix<float, 1, 3> origin;
    mat::Matrix<float, 1, 3> direction;
    float intensity;
    bool ambient;
} typedef lightColor;

struct material {
    std::string name;
    mat::Matrix<float, 1, 3> color;
    float transparency;
    float reflection;
    float refraction;
    float shininess;
    float specular;
    float diffuse;
    float ambient;
} typedef material;
