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
        virtual normalRay convertHit (cameraRay Ray, normalRay transformedHit, mat::Matrix<float, 1, 3> origin, mat::Matrix<float, 1, 3> direction) = 0;
};

class APrimitives : public IPrimitives {
    public:
        std::vector<normalRay> getIntersection () {return _ray;}
        cameraRay transformRay (cameraRay initialRay, mat::Matrix<float, 1, 3> origin, mat::Matrix<float, 1, 3> direction)
        {
            cameraRay ray;
            ray.origin = initialRay.origin - origin;
            ray.direction = initialRay.direction - direction;
            return ray;
        }
        normalRay convertHit (cameraRay Ray, normalRay transformedHit, mat::Matrix<float, 1, 3> origin, mat::Matrix<float, 1, 3> direction)
        {
            normalRay hit;
            hit.origin = Ray.origin + transformedHit.origin + origin;
            hit.direction = Ray.direction + transformedHit.direction + direction;
            hit.primitiveId = transformedHit.primitiveId;
            return hit;
        }

    protected:
        std::vector<normalRay> _ray;
};
