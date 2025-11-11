#ifndef UI_HPP
#define UI_HPP

#include "./Window.hpp"
#include "./Terrain.hpp"

class UI
{
    private:
    //
    public:
    static void init(Window &window);
    static void render(Terrain &terrain);
    static void terminate();
};

#endif