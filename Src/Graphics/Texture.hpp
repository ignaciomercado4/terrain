#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include "./GLObject.hpp"

enum class TextureType
{
    DIFFUSE,
    SPECULAR,
    NORMAL,
    EMISSIVE,
    BASE,
    UNKNOWN
};

class Texture : public GLObject
{
private:
    TextureType getTexturePathFromPath(std::string path);

public:
    unsigned int ID;
    Texture(std::string path);
    Texture();
    void bind();
    void bindToUnit(unsigned int unit);
    void unbind();
    ~Texture();
    TextureType type;
};

#endif