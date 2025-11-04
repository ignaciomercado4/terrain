#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

class Texture
{
private:
    unsigned int ID;
public:
    Texture(std::string path);
    ~Texture();
};

#endif