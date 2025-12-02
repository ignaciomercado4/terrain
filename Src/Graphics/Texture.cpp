#include <iostream>
#include "./Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>

Texture::Texture(std::string path)
{
    if (path.empty())
    {
        ID = 0;
        type = TextureType::UNKNOWN;
        std::cout << "WARNING: Empty texture path, skipping." << std::endl;
        return;
    }

    type = getTexturePathFromPath(path);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int w, h, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(path.c_str(), &w, &h, &nrChannels, 0);

    if (!data)
    {
        std::cerr << "Unable to load texture from path:" << path << ".\n";
        exit(0);
    }
    else
    {
        int format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    std::cout << "MESSAGE: Texture loaded: " << path
              << " (type: " << (int)type << ", " << w << "x" << h << ", channels=" << nrChannels << ")\n";
}

Texture::Texture()
{
    ID = 0;
    type = TextureType::UNKNOWN;
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::bindToUnit(unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

TextureType Texture::getTexturePathFromPath(std::string path)
{
    std::string filename = path.substr(path.find_last_of("/\\") + 1);

    size_t pos = filename.find("_");
    if (pos == std::string::npos)
    {
        return TextureType::UNKNOWN;
    }

    std::string prefix = filename.substr(0, pos);

    std::transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);

    if (prefix == "diffuse")
        return TextureType::DIFFUSE;
    if (prefix == "specular")
        return TextureType::SPECULAR;
    if (prefix == "normal")
        return TextureType::NORMAL;
    if (prefix == "emissive")
        return TextureType::EMISSIVE;
    if (prefix == "base")
        return TextureType::EMISSIVE;

    return TextureType::UNKNOWN;
}
