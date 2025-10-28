#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "./Shader.hpp"
#include "./GLObject.hpp"
#include "./VAO.hpp"
#include "./VBO.hpp"
#include "./Camera.hpp"
#include "./Window.hpp"
#include "./Input.hpp"
#include "./Vertex.hpp"

int main()
{
    Window window(1000, 1000, "Terrain");

    std::vector<Vertex> vertices = {
        {glm::vec3(-1.0f, 0.0f, -1.0f)},
        {glm::vec3(-1.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f, 0.0f, -1.0f)},
        {glm::vec3(-1.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f, 0.0f, -1.0f)},
        {glm::vec3(1.0f, 0.0f, 1.0f)},

        {glm::vec3(-1.0f + 2.0f, 0.0f, -1.0f)},
        {glm::vec3(-1.0f + 2.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f + 2.0f, 0.0f, -1.0f)},
        {glm::vec3(-1.0f + 2.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f + 2.0f, 0.0f, -1.0f)},
        {glm::vec3(1.0f + 2.0f, 0.0f, 1.0f)},

        {glm::vec3(-1.0f, 0.0f, -1.0f + 2.0f)},
        {glm::vec3(-1.0f, 0.0f, 1.0f + 2.0f)},
        {glm::vec3(1.0f, 0.0f, -1.0f + 2.0f)},
        {glm::vec3(-1.0f, 0.0f, 1.0f + 2.0f)},
        {glm::vec3(1.0f, 0.0f, -1.0f + 2.0f)},
        {glm::vec3(1.0f, 0.0f, 1.0f + 2.0f)},

        {glm::vec3(-1.0f + 2.0f, 0.0f, -1.0f + 2.0f)},
        {glm::vec3(-1.0f + 2.0f, 0.0f, 1.0f + 2.0f)},
        {glm::vec3(1.0f + 2.0f, 0.0f, -1.0f + 2.0f)},
        {glm::vec3(-1.0f + 2.0f, 0.0f, 1.0f + 2.0f)},
        {glm::vec3(1.0f + 2.0f, 0.0f, -1.0f + 2.0f)},
        {glm::vec3(1.0f + 2.0f, 0.0f, 1.0f + 2.0f)},
    };

    VAO vao;
    VBO vbo(GL_ARRAY_BUFFER);
    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    vao.enableVAR(0);

    Shader test("./Resources/Shaders/test.vert", "./Resources/Shaders/test.frag");
    test.use();

    Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));

    while (!glfwWindowShouldClose(window.getWindowPointer()))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::mat4 model(1.0f);
        Input::update(window, camera, model, vertices);
        glm::mat4 mvp = camera.getProjectionMatrix(window.ratio) * camera.getViewMatrix() * model;
        test.setMat4(mvp, "u_mvp");
        glDrawArrays(GL_TRIANGLES, 0, 24);

        glfwSwapBuffers(window.getWindowPointer());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
