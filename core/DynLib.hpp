/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** DLLoader
*/

#pragma once

#include <iostream>
#include <dlfcn.h>

#include <filesystem>

namespace fs = std::filesystem;

namespace RayTracer
{

    class DynLib
    {
    public:
        class DynLibException : public std::runtime_error
        {
            using std::runtime_error::runtime_error;
        };

    private:
        class DLOpenException : public DynLibException
        {
            using DynLibException::DynLibException;
        };
        class DLSymException : public DynLibException
        {
            using DynLibException::DynLibException;
        };

        typedef struct handle
        {
            void *ptr;
            std::string libname;
        } handle_t;

        handle_t _handle{};

    public:
        DynLib(const fs::path &libpath, int mode = RTLD_LAZY);
        ~DynLib();

        void *sym(const std::string &symname) const;
        std::string getLibName() const;
    };

};
