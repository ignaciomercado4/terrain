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

int main()
{
    Window window(1920, 1080, "Terrain");

    Terrain terrain(1000.0f, 2.0f / 10.f);
    terrain.setPerlinNoiseHeightValues();

    VAO vao;
    VBO vbo(GL_ARRAY_BUFFER);
    vao.bind();
    vbo.bind();
    vbo.setBufferData(terrain.vertices.size() * sizeof(Vertex), terrain.vertices.data(), GL_DYNAMIC_DRAW);
    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
    vao.enableVAR(0);
    vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
    vao.enableVAR(1);
    vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
    vao.enableVAR(2);

    VBO ebo(GL_ELEMENT_ARRAY_BUFFER);
    ebo.bind();
    ebo.setBufferData(terrain.indices.size() * sizeof(unsigned int), terrain.indices.data(), GL_DYNAMIC_DRAW);

    Shader testShader("./Resources/Shaders/test.vert", "./Resources/Shaders/test.frag");
    testShader.use();

    Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));

    Texture texture("./Resources/Textures/test.png");

    while (!glfwWindowShouldClose(window.getWindowPointer()))
    {

        vbo.bind();
        vbo.setBufferData(terrain.vertices.size() * sizeof(Vertex), terrain.vertices.data(), GL_DYNAMIC_DRAW);
        vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
        vao.enableVAR(0);
        vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
        vao.enableVAR(1);
        vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
        vao.enableVAR(2);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::mat4 model(1.0f);
        Input::update(window, camera, model, terrain.vertices, terrain.indices);
        glm::mat4 mvp = camera.getProjectionMatrix(window.ratio) * camera.getViewMatrix() * model;
        testShader.setMat4(mvp, "u_mvp");
        texture.bind();
        testShader.setInt(0, "u_texture");
        glDrawElements(GL_TRIANGLES, terrain.indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.getWindowPointer());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
