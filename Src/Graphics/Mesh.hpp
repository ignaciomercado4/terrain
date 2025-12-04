#ifndef MESH_HPP
#define MESH_HPP

#include "../Misc/Common.hpp"
#include "./Vertex.hpp"
#include "./Texture.hpp"
#include "./Shader.hpp"
#include "./VAO.hpp"
#include "./VBO.hpp"
#include <vector>

class Mesh
{
private:
    void setBuffers();

public:
    VAO vao;
    VBO vbo;
    std::vector<Texture> textures;
    VBO ebo;
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    Mesh(
        std::vector<unsigned int> _indices,
        std::vector<Vertex> _vertices,
        std::vector<Texture> _textures);
    void render(Shader &shader);
};

#endif