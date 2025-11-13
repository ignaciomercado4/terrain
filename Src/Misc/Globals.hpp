#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "../Game/Camera.hpp"
#include "../Game/Terrain.hpp"

namespace Globals
{
    extern bool isWireframe;
    extern Camera camera;
    extern Terrain* terrain;
    void init();
};

#endif