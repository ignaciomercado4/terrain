#include "./ResourceManager.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Shader.hpp"
#include <iostream>
#include <memory>
#include <filesystem>
#include <map>

void ResourceManager::init()
{
    for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(textureFolder))
    {
        std::string name = std::filesystem::path(dirEntry).filename().string();
        setTexture(name);
    }

    for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(shaderFolder))
    {
        std::string name = std::filesystem::path(dirEntry).stem().string();
        setShader(name);
    }
}

void ResourceManager::setTexture(const std::string &name)
{
    auto t = std::make_unique<Texture>(textureFolder + name);
    textures.insert({name, std::move(t)});
}

void ResourceManager::setShader(const std::string &name)
{
    auto s = std::make_unique<Shader>(shaderFolder + name + ".vert",
                                      shaderFolder + name + ".frag");
    shaders.insert({name, std::move(s)});
}

Texture *ResourceManager::getTexture(const std::string &name) const
{
    auto it = textures.find(name);

    if (it != textures.end())
    {
        return it->second.get();
    }

    std::cout << "ERROR: Texture named '" << name << "' not found in ResourceManager." << std::endl;
    return nullptr;
}

Shader *ResourceManager::getShader(const std::string &name) const
{
    auto it = shaders.find(name);

    if (it != shaders.end())
    {
        return it->second.get();
    }

    std::cout << "ERROR: Shader named '" << name << "' not found in ResourceManager." << std::endl;
    return nullptr;
}
