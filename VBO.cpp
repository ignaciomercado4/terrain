#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./VBO.hpp"

VBO::VBO(GLenum _type)
{
    type = _type;
    glGenBuffers(1, &ID);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &ID);
}

void VBO::setBufferData(GLsizeiptr size, const void *data, GLenum usage)
{
    glBufferData(type, size, data, usage);
}

void VBO::bind()
{
    glBindBuffer(type, ID);
}

void VBO::unbind()
{
    glBindBuffer(type, 0);
}

unsigned int VBO::getID()
{
    return ID;
}