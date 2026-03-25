#ifndef ITEM_HPP
#define ITEM_HPP

#include "./GameObject.hpp"
#include "../Graphics/VAO.hpp"
#include "../Graphics/VBO.hpp"
#include "../Graphics/Model.hpp"
#include <glm/glm.hpp>

enum ITEM_TYPE { NONE, WEAPON, FOOD };


class Item : public GameObject
{
private:
    VAO vao;
    VBO vbo;
    VBO ebo;
    ITEM_TYPE type =  NONE;
public:
    Item(ITEM_TYPE type);
    void setType(const ITEM_TYPE &type);
    ITEM_TYPE getType() const;
};

#endif