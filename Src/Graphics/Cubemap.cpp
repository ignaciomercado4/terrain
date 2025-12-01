#include "./Cubemap.hpp"
#include "../Misc/Common.hpp"
#include "../Misc/Globals.hpp"
#include "stb_image.h"

Cubemap::Cubemap() : vbo(GL_ARRAY_BUFFER), ebo(GL_ELEMENT_ARRAY_BUFFER)
{
    textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        stbi_set_flip_vertically_on_load(0);
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            std::cout << "MESSAGE: Loaded cubemap texture at: " << faces.at(i) << "." << std::endl;
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    setBuffers();
}

void Cubemap::setBuffers()
{
    vao.bind();
    vbo.bind();
    vbo.setBufferData(vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

    vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0));
    vao.enableVAR(0);

    ebo.bind();
    ebo.setBufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
}

void Cubemap::render()
{
    vao.bind();
    Globals::resourceManager.getShader("skybox")->use();
    glm::mat4 view = glm::mat4(glm::mat3(Globals::camera.getViewMatrix()));
    Globals::resourceManager.getShader("skybox")->setMat4(view, "u_view");
    Globals::resourceManager.getShader("skybox")->setMat4(Globals::camera.getProjectionMatrix(Globals::window->ratio), "u_projection");
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    Globals::resourceManager.getShader("skybox")->setInt(0, "u_skyboxTexture");
    
    glDepthMask(GL_FALSE);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);

    vao.unbind();
}
