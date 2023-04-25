/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Primitives
*/

#pragma once
#include <vector>
#include <map>
#include <string>
#include <libconfig.h++>
#include "struct.hpp"

class IPrimitives {
    public:
        virtual ~IPrimitives() = default;
        virtual void computeIntersection (cameraRay ray) = 0;
        virtual std::vector<normalRay> getIntersection () = 0;
        virtual mat::Matrix<float, 1, 3> getColor () = 0;
        virtual cameraRay transformRay (cameraRay initialRay, mat::Matrix<float, 1, 3> origin, mat::Matrix<float, 1, 3> direction) = 0;
        virtual normalRay convertHit (normalRay transformedHit, mat::Matrix<float, 1, 3> origin, mat::Matrix<float, 1, 3> direction) = 0;
};

class APrimitives : public IPrimitives {
    public:
        std::vector<normalRay> getIntersection () {return _ray;}
        cameraRay transformRay (cameraRay initialRay, mat::Matrix<float, 1, 3> origin, mat::Matrix<float, 1, 3> direction)
        {
            mat::Matrix<float, 3, 3> transformRotate = mat::rotationMatrix(-direction(0, 0), -direction(0, 1), -direction(0, 2));
            cameraRay transformedRay;
            transformedRay.origin = initialRay.origin - origin;
            transformedRay.direction = initialRay.direction * transformRotate;
            return transformedRay;
        }
        normalRay convertHit (normalRay transformedHit, mat::Matrix<float, 1, 3> origin, mat::Matrix<float, 1, 3> direction)
        {
            mat::Matrix<float, 3, 3> transformRotate = mat::rotationMatrix(direction(0, 0), direction(0, 1), direction(0, 2));
            normalRay convertedHit;
            convertedHit.origin = transformedHit.origin * transformRotate + origin;
            convertedHit.direction = transformedHit.direction * transformRotate;
            convertedHit.primitiveId = transformedHit.primitiveId;
            convertedHit.distance = transformedHit.distance;
            return convertedHit;
        }

    protected:
        std::vector<normalRay> _ray;
};
