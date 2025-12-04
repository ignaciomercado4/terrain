#include "./Mesh.hpp"
#include "../Misc/Utils.hpp"
#include "../Misc/Globals.hpp"
#include <iostream>

Mesh::Mesh(
    std::vector<unsigned int> _indices,
    std::vector<Vertex> _vertices,
    std::vector<Texture> _textures) :

                                      indices(_indices),
                                      vertices(_vertices),
                                      textures(_textures),
                                      vbo(GL_ARRAY_BUFFER),
                                      ebo(GL_ELEMENT_ARRAY_BUFFER)
{
    setBuffers();
}

void Mesh::setBuffers()
{
    Utils::checkGLError("Before setBuffers");
    
    vao.bind();
    
    vbo.bind();
    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    vao.enableVAR(0);
    vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    vao.enableVAR(1);
    vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    vao.enableVAR(2);
    vao.setVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    vao.enableVAR(3);
    
    ebo.bind();
    ebo.setBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
    
}

void Mesh::render(Shader &shader)
{
    vao.bind();
    Utils::checkGLError("Before glDrawElements");
    
    ebo.bind();
    
    vbo.bind();
    
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    
    Utils::checkGLError("After glDrawElements");
    
    vao.unbind();
}