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
    for (int i = 0; i < faceId.size(); i++) {
        _vertices.push_back(tmpVertices[faceId[i]]);
    }
}