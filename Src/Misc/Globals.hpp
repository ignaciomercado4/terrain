#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "../Game/Camera.hpp"
#include "../Game/Terrain.hpp"
#include "../Misc/ResourceManager.hpp"

namespace Globals
{
    extern bool isWireframe;
    extern Camera camera;
    extern Terrain* terrain;
    extern ResourceManager resourceManager;
    void init();
};

#endif