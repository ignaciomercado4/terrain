#include "./GrassPatch.hpp"
#include "../Misc/Globals.hpp"
#include <random>
#include <iostream>

GrassPatch::GrassPatch(glm::vec3 a, glm::vec3 b, glm::vec3 c, int _maxBlades) : maxBlades(_maxBlades), vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER)
{
    triangleVertices[0] = a;
    triangleVertices[1] = b;
    triangleVertices[2] = c;

    for (int i = 0; i < maxBlades; i++)
    {
        std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        float u = dist(rng);
        float v = dist(rng);

        if (u + v > 1.0f)
        {
            u = 1.0f - u;
            v = 1.0f - v;
        }

        glm::vec3 p = a + u * (b - a) + v * (c - a);
        p.y += 0.07f;
        bladePositions.push_back(p);
    }

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

void GrassPatch::renderNotInstanced()
{
    for (auto p : bladePositions)
    {
        vao.bind();
        glm::mat4 model(1.0f);
        model = glm::translate(model, p);
        model = glm::scale(model, glm::vec3(0.1f, 0.05f, 0.1f));
        Globals::resourceManager.getShader("grass")->use();
        Globals::resourceManager.getTexture("grass_blade.png")->bindToUnit(3);

        Globals::resourceManager.getShader("grass")->setMat4(model, "u_model");
        Globals::resourceManager.getShader("grass")->setMat4(Globals::camera.getViewMatrix(), "u_view");
        Globals::resourceManager.getShader("grass")->setMat4(Globals::camera.getProjectionMatrix(), "u_projection");
        Globals::resourceManager.getShader("grass")->setInt(3, "u_texture");
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    }
}