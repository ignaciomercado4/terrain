#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include "./GLObject.hpp"

class Texture : public GLObject
{
private:
    unsigned int ID;

public:
    Texture(std::string path);
    void bind();
    void bindToUnit(unsigned int unit);
    void unbind();
    ~Texture();
};

#endif