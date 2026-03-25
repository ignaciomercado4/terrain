#ifndef KNIFE_HPP
#define KNIFE_HPP

#include "./Item.hpp"
#include "../Graphics/Model.hpp"
#include "../Misc/Globals.hpp"

class Knife : public Item
{
    private:
    Model *model;
    public:
        Knife();
        void updatePosition();
        void render();
};

#endif