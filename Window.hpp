#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
    private:
        GLFWwindow* window;
    public:
        int width;
        int height;
        const char* title;
        float ratio;
        Window(int width, int height, const char* title);
        GLFWwindow* getWindowPointer();
        void swapBuffersPollEvents();
};

#endif