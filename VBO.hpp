#ifndef VBO_HPP
#define VBO_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./GLObject.hpp"

class VBO : public GLObject
{
private:
    unsigned int ID;
    GLenum type;

public:
    VBO(GLenum _type);
    ~VBO() override;
    void setBufferData(GLsizeiptr size, const void *data, GLenum usage);
    void bind() override;
    void unbind() override;
    unsigned int getID();
};

#endif