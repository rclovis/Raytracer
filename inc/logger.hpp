/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** logger
*/

#pragma once

#include "colors.hpp"

#define LOG(COLOR, WHAT, MSG) "[" << COLOR << #WHAT << RESET << "] " << MSG << std::endl

#define LOG_CORE(MSG) LOG(CYAN, core, MSG)
#define LOG_ERR_CORE(MSG) LOG(RED, core, MSG)

#define LOG_DYNLIB(MSG) LOG(GREEN, dynlib, MSG)
#define LOG_ERR_DYNLIB(MSG) LOG(RED, dynlib, MSG)

#define LOG_PARSER(MSG) LOG(MAGENTA, dynlib, MSG)
#define LOG_ERR_PARSER(MSG) LOG(RED, dynlib, MSG)
