#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../Misc/Common.hpp"
#include "./Texture.hpp"
#include <map>
#include <string>

struct Material
{
    glm::vec3 diffuse  = glm::vec3(0.8f);
    glm::vec3 ambient  = glm::vec3(0.2f);
    glm::vec3 specular = glm::vec3(0.0f);
    glm::vec3 emmisive = glm::vec3(0.0f);

    float shininess        = 0.0f;   
    float specularExponent = 0.0f;   
    float alpha            = 1.0f;   
    int illum              = 2;      

    Texture diffuseMap, specularMap, baseTexture;

    bool hasDiffuse  = false;
    bool hasSpecular = false;
    bool hasBase     = false;
};

class MaterialLoader
{
public:
    static std::map<std::string, Material> loadMTL(const std::string& path);
};

#endif
