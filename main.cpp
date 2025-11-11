#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <climits>
#include "./Shader.hpp"
#include "./GLObject.hpp"
#include "./VAO.hpp"
#include "./VBO.hpp"
#include "./Camera.hpp"
#include "./Window.hpp"
#include "./Input.hpp"
#include "./Vertex.hpp"
#include "./Texture.hpp"
#include "./Terrain.hpp"
#include "./UI.hpp"
#include "./Globals.hpp"

int main()
{
    Window window(1080, 1080, "Terrain");
    Terrain terrain(100.0f, 2.0f / 10.0f);
    terrain.setPerlinNoiseHeightValues();

    UI::init(window);

    Shader testShader("./Resources/Shaders/test.vert", "./Resources/Shaders/test.frag");
    testShader.use();

    Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));

    Texture snowGrassTexture("./Resources/Textures/snow_grass.png");
    Texture grassTexture("./Resources/Textures/grass.png");
    Texture treeTexture("./Resources/Textures/tree.png");

    while (!glfwWindowShouldClose(window.getWindowPointer()))
    {
        terrain.updateBuffers();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model(1.0f);
        Input::update(window, camera, model, terrain);
        testShader.setMat4(camera.getProjectionMatrix(window.ratio), "u_projection");
        testShader.setMat4(camera.getViewMatrix(), "u_view");
        testShader.setMat4(model, "u_model");
        testShader.setVec3(camera.getEye(), "u_viewPosition");

        snowGrassTexture.bindToUnit(0);
        testShader.setInt(0, "u_snowGrassTexture");
        grassTexture.bindToUnit(1);
        testShader.setInt(1, "u_grassTexture");

        // debug: wireframe
        if (Globals::isWireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        };

        terrain.draw();

        UI::render(terrain);

        window.swapBuffersPollEvents();
    }

    glfwTerminate();
    UI::terminate();

    return 0;
}
