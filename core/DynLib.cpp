/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** DLLoader
*/

#include "DynLib.hpp"
#include "logger.hpp"

namespace RayTracer
{
    DynLib::DynLib(const fs::path &libpath, int mode)
    {
        dlerror();
        _handle = {
            .ptr = dlopen(libpath.string().c_str(), mode),
            .libname = libpath.filename(),
        };
        char *dlerr = dlerror();
        if (dlerr != NULL)
            throw DLOpenException(dlerr);
        std::cout << LOG_DYNLIB("loaded dynlib: " << libpath.filename());
    }

    DynLib::~DynLib()
    {
        dlerror();
        dlclose(_handle.ptr);
        char *dlerr = dlerror();
        if (dlerr != NULL)
            std::cout << LOG_ERR_DYNLIB(dlerr);
        else
            std::cout << LOG_DYNLIB("closed dynlib: \"" << _handle.libname << "\"");
    }

    void *DynLib::sym(const std::string &symname) const
    {
        dlerror();
        void *symptr = dlsym(_handle.ptr, symname.c_str());
        char *dlerr = dlerror();
        if (dlerr != NULL)
            throw DLSymException(dlerr);
        return symptr;
    }

    std::string DynLib::getLibName() const
    {
        return _handle.libname;
    }
}
