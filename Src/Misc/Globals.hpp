#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "../Game/Camera.hpp"
#include "../Game/Terrain.hpp"
#include "../Misc/ResourceManager.hpp"
#include "../Graphics/Window.hpp"

namespace Globals
{
    extern bool isWireframe;
    extern Camera camera;
    extern Window* window;
    extern Terrain* terrain;
    extern ResourceManager resourceManager;
    void init();
    extern float fps;
    extern float deltaTime;
    extern float lastFrame;
};

#endif