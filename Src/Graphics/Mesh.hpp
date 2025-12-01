#ifndef MESH_HPP
#define MESH_HPP

#include "./Vertex.hpp"
#include "./VAO.hpp"
#include "./VBO.hpp"
#include "./Texture.hpp"
#include "./Shader.hpp"
#include <vector>

class Mesh
{
private:
    VAO vao;
    VBO vbo, ebo;
    void setupMesh();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void render(Shader& shader);
};

#endif