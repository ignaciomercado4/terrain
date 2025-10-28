#ifndef GLOBJECT_HPP
#define GLOBJECT_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLObject
{
    private:
    static bool contextInitialized;

    public:
    GLObject();

    static void checkContext();

    virtual void bind();
    virtual void unbind();
    virtual ~GLObject();
};

#endif