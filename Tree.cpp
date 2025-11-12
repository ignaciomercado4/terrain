#include "./Tree.hpp"
#include "./Vertex.hpp"
#include "./Globals.hpp"
#include "./Texture.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

Tree::Tree() : GameObject("Tree"), vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER)
{
    setScale(glm::vec3(0.2f));
    vao.bind();
    vbo.bind();

    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
    vao.enableVAR(0);
    vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
    vao.enableVAR(1);
    vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
    vao.enableVAR(2);
    vao.setVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(9 * sizeof(float)));
    vao.enableVAR(3);

    ebo.bind();
    ebo.setBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
}

void Tree::render()
{
    vao.bind();
    shader.use();
    texture.bindToUnit(2);
    shader.setMat4(getModelMatrix(), "u_model");
    shader.setMat4(Globals::camera.getViewMatrix(), "u_view");
    shader.setMat4(Globals::camera.getProjectionMatrix(), "u_projection");
    shader.setInt(2, "u_texture");

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}
