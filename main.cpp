#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
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
#include "./Tree.hpp"

int main()
{
    Window window(1080, 1080, "Terrain");
    Terrain terrain(10.0f, 2.0f / 10.0f);
    terrain.setPerlinNoiseHeightValues();

    UI::init(window);
    Tree tree;

    Shader testShader("./Resources/Shaders/test.vert", "./Resources/Shaders/test.frag");

    Texture snowGrassTexture("./Resources/Textures/snow_grass.png");
    Texture grassTexture("./Resources/Textures/grass.png");

    while (!glfwWindowShouldClose(window.getWindowPointer()))
    {
        terrain.updateBuffers();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model(1.0f);
        Input::update(window, model, terrain);
        testShader.use();
        testShader.setMat4(Globals::camera.getProjectionMatrix(window.ratio), "u_projection");
        testShader.setMat4(Globals::camera.getViewMatrix(), "u_view");
        testShader.setMat4(model, "u_model");
        testShader.setVec3(Globals::camera.getEye(), "u_viewPosition");

        snowGrassTexture.bindToUnit(0);
        testShader.setInt(0, "u_snowGrassTexture");
        grassTexture.bindToUnit(1);
        testShader.setInt(1, "u_grassTexture");
        
        if (Globals::isWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        terrain.draw();
        tree.render();

        UI::render(terrain);

        window.swapBuffersPollEvents();
    }

    glfwTerminate();
    UI::terminate();

    return 0;
}
