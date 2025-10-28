#ifndef VAO_HPP
#define VAO_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./GLObject.hpp"

class VAO : public GLObject
{
private:
    unsigned int ID;

public:
    VAO();
    ~VAO() override;
    static void setVertexAttributes(GLuint index, 
        GLint size, 
        GLenum type, 
        GLboolean normalized, 
        GLsizei stride, 
        const void *pointer);
    void bind() override;
    void unbind() override;
    void enableVAR(unsigned int index);
    unsigned int getID();
};

#endif