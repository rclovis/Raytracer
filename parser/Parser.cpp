/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Parser
*/

#include "Parser.hpp"


Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::setPath (std::string path)
{
    _path = path;
}

std::vector<IPrimitives *> Parser::parsePrimitives(std::map<std::string, RayTracer::DynLib*> primitivesObj)
{
    std::vector<IPrimitives *> primitives;
    libconfig::Config cfg;
    try {
        cfg.readFile(_path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cout << LOG_PARSER("I/O error while reading file.");
        return primitives;
    } catch (const libconfig::ParseException &pex) {
        std::cout << LOG_PARSER("Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError());
        return primitives;
    }
    const libconfig::Setting &root = cfg.getRoot();
    const libconfig::Setting &primitivesSetting = root["primitives"];
    for (int i = 0; i < primitivesSetting.getLength(); i++) {
        const libconfig::Setting &primitive = primitivesSetting[i];
        std::string name = primitive.getName();
        for (int j = 0; j < primitive.getLength(); j++) {
            if (primitivesObj.find(name) == primitivesObj.end()) {
                std::cout << LOG_PARSER("Primitive " << name << " not found.");
                continue;
            } else {
                std::cout << LOG_PARSER("Primitive " << name << " found.");
                InitPrimitive_t tmp = (InitPrimitive_t)primitivesObj[name]->sym("Init");

                primitives.push_back(tmp(primitive[j]));

            }
        }
    }
    return primitives;
}

std::vector<ILights *> Parser::parseLights(std::map<std::string, RayTracer::DynLib*> lightObj)
{
    std::vector<ILights *> light;
    libconfig::Config cfg;
    try {
        cfg.readFile(_path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cout << LOG_PARSER("I/O error while reading file.");
        return light;
    } catch (const libconfig::ParseException &pex) {
        std::cout << LOG_PARSER("Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError());
        return light;
    }
    const libconfig::Setting &root = cfg.getRoot();
    const libconfig::Setting &lightSetting = root["lights"];
    for (int i = 0; i < lightSetting.getLength(); i++) {
        const libconfig::Setting &light_t = lightSetting[i];
        std::string name = light_t.getName();
        for (int j = 0; j < light_t.getLength(); j++) {
            if (lightObj.find(name) == lightObj.end()) {
                std::cout << LOG_PARSER("Light " << name << " not found.");
                continue;
            } else {
                std::cout << LOG_PARSER("Light " << name << " found.");
                InitLights_t tmp = (InitLights_t)lightObj[name]->sym("Init");

                light.push_back(tmp(light_t[j]));

            }
        }
    }
    return light;
}

/*
camera :
{
    resolution = { width = 1920; height = 1080; };
    position = { x = 0; y = -100; z = 20; };
    rotation = { x = 0; y = 0; z = 0; };
    fieldOfView = 72.0; # In degree
};
*/


Camera *Parser::parseCamera ()
{
    int width, height;
    float fov;
    mat::Matrix<float, 1, 3> position, rotation;
    libconfig::Config cfg;
    try {
        cfg.readFile(_path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cout << LOG_PARSER("I/O error while reading file.");
        return new Camera(width, height, position, rotation, fov);
    } catch (const libconfig::ParseException &pex) {
        std::cout << LOG_PARSER("Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError());
        return new Camera(width, height, position, rotation, fov);
    }
    const libconfig::Setting &root = cfg.getRoot();
    const libconfig::Setting &cameraSetting = root["camera"];
    const libconfig::Setting &resolutionSetting = cameraSetting["resolution"];
    resolutionSetting.lookupValue("width", width);
    resolutionSetting.lookupValue("height", height);
    const libconfig::Setting &positionSetting = cameraSetting["position"];
    int x, y, z;
    positionSetting.lookupValue("x", x);
    positionSetting.lookupValue("y", y);
    positionSetting.lookupValue("z", z);
    position = {{(float)x, (float)y, (float)z}};
    const libconfig::Setting &rotationSetting = cameraSetting["rotation"];
    rotationSetting.lookupValue("x", x);
    rotationSetting.lookupValue("y", y);
    rotationSetting.lookupValue("z", z);
    rotation = {{(float)x, (float)y, (float)z}};
    cameraSetting.lookupValue("fieldOfView", fov);
    return new Camera(width, height, position, rotation, fov);
}