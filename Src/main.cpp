#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <iomanip>
#include "./Graphics/Shader.hpp"
#include "./Graphics/GLObject.hpp"
#include "./Graphics/VAO.hpp"
#include "./Graphics/VBO.hpp"
#include "./Graphics/Window.hpp"
#include "./Graphics/Vertex.hpp"
#include "./Graphics/Texture.hpp"
#include "./Game/Camera.hpp"
#include "./Game/Input.hpp"
#include "./Game/Terrain.hpp"
#include "./Game/UI.hpp"
#include "./Game/Tree.hpp"
#include "./Misc/Globals.hpp"

int main()
{
    Window window(1080, 1080, "Terrain");

    Globals::init();
    Globals::resourceManager.init();
    Globals::terrain->setPerlinNoiseHeightValues();

    UI::init(window);

    while (!glfwWindowShouldClose(window.getWindowPointer()))
    {
        Globals::terrain->updateBuffers();


        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model(1.0f);
        Input::update(window, model);
        
        Globals::resourceManager.getShader("terrain")->use();
        Globals::resourceManager.getShader("terrain")->setMat4(Globals::camera.getProjectionMatrix(window.ratio), "u_projection");
        Globals::resourceManager.getShader("terrain")->setMat4(Globals::camera.getViewMatrix(), "u_view");
        Globals::resourceManager.getShader("terrain")->setMat4(model, "u_model");
        Globals::resourceManager.getShader("terrain")->setVec3(Globals::camera.getEye(), "u_viewPosition");

        Globals::resourceManager.getTexture("snow_grass.png")->bindToUnit(0);
        Globals::resourceManager.getShader("terrain")->setInt(0, "u_snowGrassTexture");
        Globals::resourceManager.getTexture("grassTexture.png")->bindToUnit(1);
        Globals::resourceManager.getShader("terrain")->setInt(1, "u_grassTexture");
        
        if (Globals::isWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        Globals::terrain->draw();
        Globals::terrain->renderTrees();


        UI::render();

        window.swapBuffersPollEvents();
    }

    glfwTerminate();
    UI::terminate();

    return 0;
}
