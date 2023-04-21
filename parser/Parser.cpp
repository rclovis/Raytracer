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
        std::cout << LOG_PARSER("I/O error while reading file.") << std::endl;
        return primitives;
    } catch (const libconfig::ParseException &pex) {
        std::cout << LOG_PARSER("Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()) << std::endl;
        return primitives;
    }
    const libconfig::Setting &root = cfg.getRoot();
    const libconfig::Setting &primitivesSetting = root["primitives"];
    for (int i = 0; i < primitivesSetting.getLength(); i++) {
        const libconfig::Setting &primitive = primitivesSetting[i];
        std::string name = primitive.getName();
        for (int j = 0; j < primitive.getLength(); j++) {
            if (primitivesObj.find(name) == primitivesObj.end()) {
                std::cout << LOG_PARSER("Primitive " << name << " not found.") << std::endl;
                continue;
            } else {
                std::cout << LOG_PARSER("Primitive " << name << " found.") << std::endl;
                InitPrimitive_t tmp = (InitPrimitive_t)primitivesObj[name]->sym("Init");

                primitives.push_back(tmp(primitive[j]));

            }
        }
    }
    return primitives;
}

std::vector<ILights *> Parser::parseLights()
{
    // std::vector<ILights *> lights;
    // libconfig::Config cfg;
    // cfg.readFile(_path.c_str());
    // const libconfig::Setting &root = cfg.getRoot();
    // const libconfig::Setting &lightsSetting = root["lights"];
    // for (int i = 0; i < lightsSetting.getLength(); i++) {
    //     const libconfig::Setting &light = lightsSetting[i];
    //     std::string type = light["type"];
    //     std::string id = light["id"];
    //     std::string conf = light["conf"];
    //     lights.push_back(Init(type, id, conf));
    // }
    // return lights;
}