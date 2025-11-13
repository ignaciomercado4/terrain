#include "./Globals.hpp"
#include "../Game/Camera.hpp"

#define TERRAIN_GRID_SIZE 100.0f
#define TERRAIN_QUAD_SIZE 10.0f

bool Globals::isWireframe = false;
Camera Globals::camera;
Terrain* Globals::terrain = nullptr;

void Globals::init()
{
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));
    terrain = new Terrain(TERRAIN_GRID_SIZE, 2.0f / TERRAIN_QUAD_SIZE);
}
