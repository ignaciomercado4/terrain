#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./Window.hpp"
#include "./GLObject.hpp"

Window::Window(int _width, int _height, const char *_title)
{
    if (!glfwInit())
    {
        std::cout << "Failed to init GLFW\n";
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    glViewport(0, 0, _width, _height);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    // glfwSwapInterval(0); // no cap

    glewExperimental = 1;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to init GLEW\n";
        exit(-1);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLObject::checkContext();
    int fbw, fbh;
    glfwGetFramebufferSize(window, &fbw, &fbh);
    glViewport(0, 0, fbw, fbh);

    ratio = (float)fbw / (float)fbh;
    width = fbw;
    height = fbh;
    title = _title;
}

GLFWwindow *Window::getWindowPointer()
{
    return window;
}

void Window::swapBuffersPollEvents()
{
    glfwSwapBuffers(getWindowPointer());
    glfwPollEvents();
}