#include "./Mesh.hpp"
#include "../Misc/Utils.hpp"
#include "../Misc/Globals.hpp"
#include <iostream>

Mesh::Mesh(
    std::vector<unsigned int> _indices,
    std::vector<Vertex> _vertices,
    std::vector<Texture> _textures,
    const Material &_material)

    : indices(_indices),
      vertices(_vertices),
      textures(_textures),
      material(_material),
      hasMaterial(true),
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
    shader.use();
    shader.setMat4(Globals::camera.getProjectionMatrix(Globals::window->ratio), "u_projection");
    shader.setMat4(Globals::camera.getViewMatrix(), "u_view");
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(15.0f, 0.0f, 4.0f));
    model = glm::scale(model, glm::vec3(0.2f));
    shader.setMat4(model, "u_model");
    shader.setVec3(Globals::camera.getEye(), "u_viewPos");
    shader.setVec3(glm::vec3(15.0f, 50.0f, 15.0f), "u_lightPos");
    shader.setVec3(glm::vec3(0.65f, 0.73f, 0.71f), "u_lightColor");

    if (hasMaterial)
    {
        shader.setVec3(material.diffuse, "material.diffuse");
        shader.setVec3(material.ambient, "material.ambient");
        shader.setVec3(material.specular, "material.specular");
        shader.setVec3(material.emmisive, "material.emmisive");

        shader.setFloat(material.shininess, "material.shininess");
        shader.setFloat(material.alpha, "material.alpha");
        shader.setInt(material.hasDiffuse ? 1 : 0, "material.hasDiffuse");
        shader.setInt(material.hasSpecular ? 1 : 0, "material.hasSpecular");
        shader.setInt(material.hasBump ? 1 : 0, "material.hasBump");
        shader.setInt(material.hasEmissive ? 1 : 0, "material.hasEmissive");
        shader.setInt(material.hasTransparency ? 1 : 0, "material.hasTransparency");


        int texUnit = 0;

        if (material.hasDiffuse)
        {
            material.diffuseMap->bindToUnit(texUnit);
            shader.setInt(texUnit, "material.diffuseMap");
            texUnit++;
        }
        if (material.hasSpecular)
        {
            material.specularMap->bindToUnit(texUnit);
            shader.setInt(texUnit, "material.specularMap");
            texUnit++;
        }
        if (material.hasBump)
        {
            material.bumpMap->bindToUnit(texUnit);
            shader.setInt(texUnit, "material.bumpMap");
            texUnit++;
        }
        if (material.hasTransparency)
        {
            material.transparencyMap->bindToUnit(texUnit);
            shader.setInt(texUnit, "material.transparencyMap");
            texUnit++;
        }
        if (material.hasEmissive)
        {
            material.emissiveMap->bindToUnit(texUnit);
            shader.setInt(texUnit, "material.emissiveMap");
            texUnit++;
        }
    }

    vao.bind();
    ebo.bind();

    Utils::checkGLError("Tex");
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.unbind();
}
