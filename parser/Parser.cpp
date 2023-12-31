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
        std::cout << LOG_ERR_PARSER("I/O error while reading file.");
        return primitives;
    } catch (const libconfig::ParseException &pex) {
        std::cout << LOG_ERR_PARSER("Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError());
        return primitives;
    }
    const libconfig::Setting &root = cfg.getRoot();
    const libconfig::Setting &primitivesSetting = root["primitives"];
    for (int i = 0; i < primitivesSetting.getLength(); i++) {
        const libconfig::Setting &primitive = primitivesSetting[i];
        std::string name = primitive.getName();
        for (int j = 0; j < primitive.getLength(); j++) {
            if (primitivesObj.find(name) == primitivesObj.end()) {
                std::cout << LOG_ERR_PARSER("Primitive " << name << " not found.");
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
        return new Camera(width, height, position, rotation, fov, antiAliasing());
    } catch (const libconfig::ParseException &pex) {
        std::cout << LOG_PARSER("Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError());
        return new Camera(width, height, position, rotation, fov, antiAliasing());
    }
    const libconfig::Setting &root = cfg.getRoot();
    const libconfig::Setting &cameraSetting = root["camera"];
    const libconfig::Setting &resolutionSetting = cameraSetting["resolution"];
    resolutionSetting.lookupValue("width", width);
    resolutionSetting.lookupValue("height", height);
    if (antiAliasing() == true) {
        width *= 2;
        height *= 2;
    }
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
    return new Camera(width, height, position, rotation, fov, antiAliasing());
}

void Parser::loadMaterials(std::vector<IPrimitives *> primitives)
{
    std::vector<material> materials;
    libconfig::Config cfg;
    try {
        cfg.readFile(_path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cout << LOG_PARSER("I/O error while reading file.");
        return;
    } catch (const libconfig::ParseException &pex) {
        std::cout << LOG_PARSER("Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError());
        return;
    }
    const libconfig::Setting &root = cfg.getRoot();
    const libconfig::Setting &materialsSetting = root["materials"];
    for (int i = 0; i < materialsSetting.getLength(); i++) {
        const libconfig::Setting &material = materialsSetting[i];
        for (int j = 0; j < material.getLength(); j++) {
            std::string name;
            int r, g, b;
            float transparency, reflection, refraction, shininess, specular, diffuse, ambient;
            material[j].lookupValue("name", name);
            material[j].lookupValue("r", r);
            material[j].lookupValue("g", g);
            material[j].lookupValue("b", b);
            material[j].lookupValue("transparency", transparency);
            material[j].lookupValue("reflection", reflection);
            material[j].lookupValue("refraction", refraction);
            material[j].lookupValue("shininess", shininess);
            material[j].lookupValue("specular", specular);
            material[j].lookupValue("diffuse", diffuse);
            material[j].lookupValue("ambient", ambient);
            materials.push_back({name, {{(float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f}}, transparency, reflection, refraction, shininess, specular, diffuse, ambient});
        }
    }

    for (int i = 0; i < primitives.size(); i++) {
        for (int j = 0; j < materials.size(); j++) {
            if (primitives[i]->getMaterialName() == materials[j].name) {
                primitives[i]->setMaterial(materials[j]);
                break;
            }
        }
    }
}

bool Parser::antiAliasing()
{
    libconfig::Config cfg;
    try {
        cfg.readFile(_path.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cout << LOG_PARSER("I/O error while reading file.");
        return false;
    } catch (const libconfig::ParseException &pex) {
        std::cout << LOG_PARSER("Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError());
        return false;
    }
    const libconfig::Setting &root = cfg.getRoot();
    int antiAliasing;
    root.lookupValue("antiAliasing", antiAliasing);
    std::cout << LOG_PARSER("antiAliasing : " << ((antiAliasing) ? "true." : "false."));
    return (antiAliasing) ? true : false;
}
