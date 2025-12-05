#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../Misc/Common.hpp"
#include "./Texture.hpp"
#include <map>
#include <string>
#include <memory>

struct Material
{
    glm::vec3 diffuse = glm::vec3(0.8f);
    glm::vec3 ambient = glm::vec3(0.2f);
    glm::vec3 specular = glm::vec3(0.0f);
    glm::vec3 emmisive = glm::vec3(0.0f);

    float shininess = 0.0f;
    float specularExponent = 0.0f;
    float alpha = 1.0f;
    int illum = 2;
    
    std::shared_ptr<Texture> diffuseMap;
    std::shared_ptr<Texture> specularMap;
    std::shared_ptr<Texture> bumpMap;
    std::shared_ptr<Texture> transparencyMap;
    std::shared_ptr<Texture> emissiveMap;

    bool hasDiffuse = false;
    bool hasSpecular = false;
    bool hasBump = false;
    bool hasTransparency = false;
    bool hasEmissive = false;
};

class MaterialLoader
{
public:
    static std::map<std::string, Material> loadMTL(const std::string &path, const std::string &dir);
};

#endif
