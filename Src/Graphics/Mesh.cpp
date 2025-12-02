#include "./Mesh.hpp"
#include "../Misc/Globals.hpp"

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
    vao.bind();
    vbo.bind();

    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0));
    vao.enableVAR(0);
    vao.setVertexAttributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));
    vao.enableVAR(1);
    vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(7 * sizeof(float)));
    vao.enableVAR(2);
    vao.setVertexAttributes(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(9 * sizeof(float)));
    vao.enableVAR(3);

    ebo.bind();
    ebo.setBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    vao.unbind();
}

void Mesh::render(Shader &shader)
{
    shader.use();
    glm::mat4 model(1.0f);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    shader.setMat4(Globals::camera.getProjectionMatrix(Globals::window->ratio), "u_projection");
    shader.setMat4(Globals::camera.getViewMatrix(), "u_view");
    shader.setMat4(model, "u_model");

    vao.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    vao.unbind();
}
