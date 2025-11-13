#ifndef TREE_HPP
#define TREE_HPP

#include "./GameObject.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/VAO.hpp"
#include "../Graphics/VBO.hpp"
#include "../Graphics/Vertex.hpp"
#include "../Graphics/Shader.hpp"
#include <vector>

class Tree : public GameObject
{
private:
    Texture texture = Texture("./Resources/Textures/tree.png");
    VAO vao;
    VBO vbo;
    VBO ebo;
    Shader shader = Shader("./Resources/Shaders/tree.vert",
                           "./Resources/Shaders/tree.frag");

    const std::vector<Vertex> vertices = {
        {{-1.0f, -2.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, -2.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, 2.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{-1.0f, 2.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

        {{0.0f, -2.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.0f, -2.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.0f, 2.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.0f, 2.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    };

    const std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4};

public:
    Tree();
    void render() override;
};

#endif