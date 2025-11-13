#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &ID);
}

void VAO::setVertexAttributes(GLuint index,
                              GLint size,
                              GLenum type,
                              GLboolean normalized,
                              GLsizei stride,
                              const void *pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VAO::bind()
{
    glBindVertexArray(ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

unsigned int VAO::getID()
{
    return ID;
}


void VAO::enableVAR(unsigned int index)
{
    glEnableVertexAttribArray(index);
}