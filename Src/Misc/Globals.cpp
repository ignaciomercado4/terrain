#include "./Globals.hpp"
#include "../Game/Camera.hpp"
#include "../Graphics/Window.hpp"

#define TERRAIN_GRID_SIZE 100.0f
#define TERRAIN_QUAD_SIZE 5.0f
#define WINDOW_HEIGHT 1080
#define WINDOW_WIDTH 1920

bool Globals::isWireframe = false;
Camera Globals::camera;
Terrain* Globals::terrain = nullptr;
Window* Globals::window = nullptr;
ResourceManager Globals::resourceManager;
float Globals::deltaTime = 0.0f;
float Globals::lastFrame = 0.0f;
float Globals::fps = 0.0f;

void Globals::init()
{
    Globals::camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));
    Globals::window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Terrain");
    Globals::terrain = new Terrain(TERRAIN_GRID_SIZE, 2.0f / TERRAIN_QUAD_SIZE, 250);
    Globals::resourceManager = ResourceManager();
}
