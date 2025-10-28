#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "./Window.hpp"
#include "./Camera.hpp"
#include "./Vertex.hpp"


class Input
{
    private:
    public:
        static void update(Window &window, Camera &camera, glm::mat4 model, std::vector<Vertex> &vertices);
};