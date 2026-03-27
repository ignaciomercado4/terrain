#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <iomanip>
#include "./Graphics/Shader.hpp"
#include "./Graphics/GLObject.hpp"
#include "./Graphics/Window.hpp"
#include "./Graphics/Texture.hpp"
#include "./Graphics/Cubemap.hpp"
#include "./Graphics/Model.hpp"
#include "./Game/Camera.hpp"
#include "./Game/Input.hpp"
#include "./Game/Terrain.hpp"
#include "./Game/Knife.hpp"
#include "./Game/UI.hpp"
#include "./Game/Tree.hpp"
#include "./Game/Collider.hpp"
#include "./Misc/Globals.hpp"
#include "./Misc/Utils.hpp"

int main()
{
    Globals::init();
    Globals::resourceManager.init();
    Globals::terrain->setPerlinNoiseHeightValues();
    UI::init(*Globals::window);
    Cubemap skybox;
    Knife knife;
    AABB camColliderTest;
    AABB randomColliderTest;

    while (!glfwWindowShouldClose(Globals::window->getWindowPointer()))
    {
        Utils::updateTiming();
        randomColliderTest.min = glm::vec3(0.0f);
        randomColliderTest.max = glm::vec3(1.0f);
        glm::vec3 camMin(Globals::camera.getEye().x, Globals::camera.getEye().y, Globals::camera.getEye().z + 0.5);
        glm::vec3 camMax(Globals::camera.getEye().x + 0.5, Globals::camera.getEye().y + 0.5, Globals::camera.getEye().z - 0.5);
        camColliderTest.min = camMin;
        camColliderTest.max = camMax;

        if (Collider::checkCollisionAABB(randomColliderTest, camColliderTest))
        {
            std::cout << "Colliding!" << std::endl;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Input::update(*Globals::window, Globals::terrain->model);
        skybox.render();

        if (Globals::isWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        Globals::terrain->render();
        Globals::terrain->renderTrees();
        Globals::terrain->renderVegetation();
        knife.render();

        UI::render();

        Globals::window->swapBuffersPollEvents();
    }

    glfwTerminate();
    UI::terminate();

    return 0;
}
