#include <iostream>
#include "./GLObject.hpp"

bool GLObject::contextInitialized = false;

GLObject::GLObject()
{
    if (!contextInitialized)
    {
        std::cerr << "ERROR: No active OpenGL context found.\n";
        std::exit(EXIT_FAILURE);
    }
}

void GLObject::checkContext()
{
    if (!glfwGetCurrentContext())
    {
        std::cerr << "ERROR: No active GLFW context.\n";
        std::exit(EXIT_FAILURE);
    }
    contextInitialized = true;
}

void GLObject::bind() {};
void GLObject::unbind() {};
GLObject::~GLObject() {}