/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** struct
*/

#pragma once
#include "Matrice.hpp"

struct normalRay {
    Matrix<float, 1, 3> origin;
    Matrix<float, 1, 3> direction;
    Matrix<float, 1, 2> uv;
} typedef normalRay;

struct cameraRay {
    Matrix<float, 1, 3> origin;
    Matrix<float, 1, 3> direction;
} typedef cameraRay;