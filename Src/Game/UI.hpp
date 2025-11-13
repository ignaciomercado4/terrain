#ifndef UI_HPP
#define UI_HPP

#include "../Graphics/Window.hpp"

class UI
{
    private:
    //
    public:
    static void init(Window &window);
    static void render();
    static void terminate();
};

#endif