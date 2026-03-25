#include "./Item.hpp"

Item::Item(ITEM_TYPE type) : type(type) {};

void Item::setType(const ITEM_TYPE &typ)
{
    type = typ;
}

ITEM_TYPE Item::getType() const
{
    return type;
}