/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Obj
*/

#include "Obj.hpp"

/*
    obj = (
        { path = "obj/teapot.obj"; x = 0; y = 0; z = 0; xr = 0; yr = 0; zr = 0; material = "blue";}
    )
*/

Obj::Obj(libconfig::Setting &conf)
{
    std::string path;
    conf.lookupValue("path", path);
    conf.lookupValue("x", _position(0, 0));
    conf.lookupValue("y", _position(0, 1));
    conf.lookupValue("z", _position(0, 2));
    conf.lookupValue("xr", _rotation(0, 0));
    conf.lookupValue("yr", _rotation(0, 1));
    conf.lookupValue("zr", _rotation(0, 2));
    conf.lookupValue("material", _materialName);
    loadObj(path);
}

Obj::~Obj()
{
}

std::vector<normalRay> Obj::computeIntersection (cameraRay ray)
{
    std::vector<normalRay> rays;
    ray = transformRay(ray, _position, _rotation);
    int index = 0;
    for (int i = 0;i < _vertices.size();i += 3) {
        point_a = _vertices[i];
        point_b = _vertices[i + 1];
        point_c = _vertices[i + 2];
        _normal = _normals[index];
        std::vector<normalRay> tmp = computeIntersectionTriangle(ray);
        for (int j = 0;j < tmp.size();j++) {
            rays.push_back(convertHit(tmp[j], _position, _rotation));
        }
        index++;
    }
    return rays;
}


void Obj::loadObj (std::string fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return;
    }

    std::vector<unsigned int> index;

    std::vector<mat::Matrix<float, 1, 3>> tmpVertices;
    std::vector<int> faceId;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v") {
            mat::Matrix<float, 1, 3> vertex;
            iss >> vertex(0, 0) >> vertex(0, 1) >> vertex(0, 2);
            tmpVertices.push_back(vertex);

        } else if (type == "f") {
            std::string vertex1, vertex2, vertex3;
            iss >> vertex1 >> vertex2 >> vertex3;

            faceId.push_back(std::stoi(vertex1.substr(0, vertex1.find("/"))) - 1);
            faceId.push_back(std::stoi(vertex2.substr(0, vertex2.find("/"))) - 1);
            faceId.push_back(std::stoi(vertex3.substr(0, vertex3.find("/"))) - 1);
        }
    }

    for (int i = 0; i < faceId.size(); i += 3) {
        mat::Matrix<float, 1, 3> vertex1 = tmpVertices[faceId[i]];
        mat::Matrix<float, 1, 3> vertex2 = tmpVertices[faceId[i + 1]];
        mat::Matrix<float, 1, 3> vertex3 = tmpVertices[faceId[i + 2]];
        mat::Matrix<float, 1, 3> normal = mat::crossProduct(vertex2 - vertex1, vertex3 - vertex1);
        normal = mat::normalizeVector(normal);
        _vertices.push_back(vertex1);
        _vertices.push_back(vertex2);
        _vertices.push_back(vertex3);
        _normals.push_back(normal);
    }
}

std::vector<normalRay> Obj::computeIntersectionTriangle(cameraRay ray)
{
    std::vector<normalRay> rays;
    float D = - (mat::dotProduct(_normal, point_a));
    if (abs(D) <= 1e-6) // maybe just D == 0
        return rays;
    if (mat::dotProduct(_normal, ray.direction) == 0)
        return rays;
    float t = (- (mat::dotProduct(_normal, ray.origin) + D)) / mat::dotProduct(_normal, ray.direction);
    if (t < 0)
        return rays;
    mat::Matrix<float, 1, 3> inter = {{ray.origin(0, 0) + (ray.direction(0, 0) * t), ray.origin(0, 1) + (ray.direction(0, 1) * t), ray.origin(0, 2) + (ray.direction(0, 2) * t)}};

    mat::Matrix<float, 1, 3> edge0 = point_b - point_a;
    mat::Matrix<float, 1, 3> vp0 = inter - point_a;
    mat::Matrix<float, 1, 3> C = mat::crossProduct(edge0, vp0);
    if (mat::dotProduct(_normal, C) < 0) return rays;

    mat::Matrix<float, 1, 3> edge1 = point_c - point_b;
    mat::Matrix<float, 1, 3> vp1 = inter - point_b;
    C = mat::crossProduct(edge1, vp1);
    if (mat::dotProduct(_normal, C) < 0) return rays;

    mat::Matrix<float, 1, 3> edge2 = point_a - point_c;
    mat::Matrix<float, 1, 3> vp2 = inter - point_c;
    C = mat::crossProduct(edge2, vp2);
    if (mat::dotProduct(_normal, C) < 0) return rays;

    normalRay normal;
    normal.origin = inter;
    normal.direction = _normal;
    if (mat::dotProduct(_normal, ray.direction) > 0)
        normal.direction *= -1;
    rays.push_back(normal);
    return rays;
}