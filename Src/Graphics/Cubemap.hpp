#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <iostream>
#include <vector>
#include "./VAO.hpp"
#include "./VBO.hpp"
#include "./Vertex.hpp"

class Cubemap
{
private:
    VAO vao;
    VBO vbo;
    VBO ebo;
    unsigned int textureID;

    std::vector<float> vertices = {
        -1.0f,
        -1.0f,
        -1.0f,
        1.0f,
        -1.0f,
        -1.0f,
        1.0f,
        1.0f,
        -1.0f,
        -1.0f,
        1.0f,
        -1.0f,
        -1.0f,
        -1.0f,
        1.0f,
        1.0f,
        -1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        -1.0f,
        1.0f,
        1.0f,
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0,

        0, 3, 7,
        7, 4, 0,

        1, 5, 6,
        6, 2, 1,

        4, 7, 6,
        6, 5, 4,

        3, 2, 6,
        6, 7, 3,

        0, 4, 5,
        5, 1, 0};

    std::vector<std::string> faces = {
        "./Resources/Cubemaps/skybox_right.jpg",
        "./Resources/Cubemaps/skybox_left.jpg",
        "./Resources/Cubemaps/skybox_top.jpg",
        "./Resources/Cubemaps/skybox_bottom.jpg",
        "./Resources/Cubemaps/skybox_front.jpg",
        "./Resources/Cubemaps/skybox_back.jpg"};

public:
    Cubemap();
    void setBuffers();
    void render();
};

#endif