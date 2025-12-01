#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include "./GLObject.hpp"

enum class TextureType {
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
    unsigned int ID;
    TextureType getTexturePathFromPath(std::string path);

public:
    Texture(std::string path);
    void bind();
    void bindToUnit(unsigned int unit);
    void unbind();
    ~Texture();
    TextureType type;
};

#endif