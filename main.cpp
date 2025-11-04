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
#include "./Texture.hpp"

int main()
{
    Window window(1000, 1000, "Terrain");

    std::vector<Vertex> vertices;
    int gridSize = 10;                
    float quadSize = 2.0f / gridSize; 

    for (int i = 0; i <= gridSize; i++)
    {
        for (int j = 0; j <= gridSize; j++)
        {
            float x = -1.0f + j * quadSize;
            float z = -1.0f + i * quadSize;
            vertices.push_back({{x, 0.0f, z}, {(float)i/10.0f, (float)i/10.0f, (float)i/10.0f, 1.0f}});
        }
    }

    std::vector<unsigned int> indices;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            int row1 = i * (gridSize + 1);
            int row2 = (i + 1) * (gridSize + 1);

            int v0 = row1 + j;
            int v1 = row2 + j;
            int v2 = row2 + j + 1;
            int v3 = row1 + j + 1;

            indices.push_back(v0);
            indices.push_back(v1);
            indices.push_back(v2);

            indices.push_back(v0);
            indices.push_back(v2);
            indices.push_back(v3);
        }
    };


    VAO vao;
    VBO vbo(GL_ARRAY_BUFFER);
    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
    vao.enableVAR(0);
    vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
    vao.enableVAR(1);

    VBO ebo(GL_ELEMENT_ARRAY_BUFFER);
    ebo.bind();
    ebo.setBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

    Shader testShader("./Resources/Shaders/test.vert", "./Resources/Shaders/test.frag");
    testShader.use();

    Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));

    Texture texture("./Resources/Textures/test.png");

    while (!glfwWindowShouldClose(window.getWindowPointer()))
    {

        vbo.bind();
        vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
        vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
        vao.enableVAR(0);
        vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
        vao.enableVAR(1);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::mat4 model(1.0f);
        Input::update(window, camera, model, vertices, indices);
        glm::mat4 mvp = camera.getProjectionMatrix(window.ratio) * camera.getViewMatrix() * model;
        testShader.setMat4(mvp, "u_mvp");
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.getWindowPointer());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
