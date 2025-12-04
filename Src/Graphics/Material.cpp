#include "./Material.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::map<std::string, Material> MaterialLoader::loadMTL(const std::string &path)
{
    std::ifstream file(path);
    if (!file.good())
    {
        std::cout << "ERROR: .mtl file not found at path: " << path << std::endl;
        exit(-1);
    }

    std::map<std::string, Material> materials;
    Material currentMaterial;
    std::string currentName;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.rfind("newmtl ", 0) == 0)
        {
            if (!currentName.empty())
            {
                materials[currentName] = currentMaterial;
            }

            currentMaterial = Material();
            currentName = line.substr(7);
        }
        else if (line.rfind("Ka ", 0) == 0)
        {
            sscanf(line.c_str(), "Ka %f %f %f",
                   &currentMaterial.ambient.x,
                   &currentMaterial.ambient.y,
                   &currentMaterial.ambient.z);
        }
        else if (line.rfind("Kd ", 0) == 0)
        {
            sscanf(line.c_str(), "Kd %f %f %f",
                   &currentMaterial.diffuse.x,
                   &currentMaterial.diffuse.y,
                   &currentMaterial.diffuse.z);
        }
        else if (line.rfind("Ks ", 0) == 0)
        {
            sscanf(line.c_str(), "Ks %f %f %f",
                   &currentMaterial.specular.x,
                   &currentMaterial.specular.y,
                   &currentMaterial.specular.z);
        }
        else if (line.rfind("Ke ", 0) == 0)
        {
            sscanf(line.c_str(), "Ke %f %f %f",
                   &currentMaterial.emmisive.x,
                   &currentMaterial.emmisive.y,
                   &currentMaterial.emmisive.z);
        }
        else if (line.rfind("Ns ", 0) == 0)
        {
            sscanf(line.c_str(), "Ns %f", &currentMaterial.shininess);
        }
        else if (line.rfind("Ni ", 0) == 0)
        {
            sscanf(line.c_str(), "Ni %f", &currentMaterial.specularExponent);
        }
        else if (line.rfind("d ", 0) == 0)
        {
            sscanf(line.c_str(), "d %f", &currentMaterial.alpha);
        }
        else if (line.rfind("illum ", 0) == 0)
        {
            sscanf(line.c_str(), "illum %d", &currentMaterial.illum);
        }
        else if (line.rfind("map_Kd ", 0) == 0)
        {
            currentMaterial.diffuseMap = Texture(line.substr(7));
            currentMaterial.hasDiffuse = true;
        }
        else if (line.rfind("map_Ks ", 0) == 0)
        {
            currentMaterial.specularMap = Texture(line.substr(7));
            currentMaterial.hasSpecular = true;
        }
    }

    if (!currentName.empty())
    {
        materials[currentName] = currentMaterial;
    }

    return materials;
}
