#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "./Camera.hpp"
#include "./Terrain.hpp"

namespace Globals
{
    extern bool isWireframe;
    extern Camera camera;
    extern Terrain* terrain;
    void init();
};

#endif