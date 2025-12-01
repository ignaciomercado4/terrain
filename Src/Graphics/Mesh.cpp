#include "./Mesh.hpp"
#include "../Misc/Globals.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER)
{
    this->indices = indices;
    this->vertices = vertices;
    this->textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // pos
    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
    vao.enableVAR(0);
    // color
    vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
    vao.enableVAR(1);
    // UV
    vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
    vao.enableVAR(2);
    // normal
    vao.setVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(9 * sizeof(float)));
    vao.enableVAR(3);

    ebo.bind();
    ebo.setBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Mesh::render(Shader& shader)
{
    shader.use();
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
}

