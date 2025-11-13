#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../Graphics/Window.hpp"
#include "../Graphics/Vertex.hpp"
#include "./Terrain.hpp"
#include "./Camera.hpp"

class Input
{
private:
public:
    static void update(Window &window, glm::mat4 model);
};