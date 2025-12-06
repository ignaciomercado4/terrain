#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include "../Graphics/Texture.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Model.hpp"

class ResourceManager
{
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<Model>> models;

    std::string textureFolder = "./Resources/Textures/";
    std::string shaderFolder = "./Resources/Shaders/";
    std::string modelFolder = "./Resources/Models";

public:
    void init();
    void setTexture(const std::string &name);
    void setShader(const std::string &name);
    void setModel(const std::string &path, const std::string &name);
    Texture* getTexture(const std::string &name) const;
    Shader* getShader(const std::string &name) const;
    Model* getModel(const std::string &name) const;
};

#endif