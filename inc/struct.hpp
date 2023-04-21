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
} typedef normalRay;

struct cameraRay {
    mat::Matrix<float, 1, 3> origin;
    mat::Matrix<float, 1, 3> direction;
} typedef cameraRay;
