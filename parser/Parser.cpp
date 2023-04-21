/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-raytracer-clovis.rabot
** File description:
** Parser
*/

#include "Parser.hpp"
#include "logger.hpp"

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

std::vector<IPrimitives *> Parser::parsePrimitives()
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