#include "./Globals.hpp"
#include "../Game/Camera.hpp"

#define TERRAIN_GRID_SIZE 100.0f
#define TERRAIN_QUAD_SIZE 10.0f

bool Globals::isWireframe = false;
Camera Globals::camera;
Terrain* Globals::terrain = nullptr;
ResourceManager Globals::resourceManager;
float Globals::deltaTime = 0.0f;
float Globals::lastFrame = 0.0f;
float Globals::fps = 0.0f;

void Globals::init()
{
    Globals::camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));
    Globals::terrain = new Terrain(TERRAIN_GRID_SIZE, 2.0f / TERRAIN_QUAD_SIZE, 25);
    Globals::resourceManager = ResourceManager();
}
