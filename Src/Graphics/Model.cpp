#include "./Model.hpp"
#include "./Mesh.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "../Misc/Globals.hpp"
#include "../Misc/Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <memory>

Model::Model(std::string path)
{
    loadOBJ(path);
    std::cout << "MESSAGE: Loaded OBJ model at path:" << path << std::endl;
}

void Model::loadOBJ(std::string path)
{
    temp_positions.clear();
    temp_uvs.clear();
    temp_normals.clear();

    std::ifstream file(path);
    if (!file.good())
    {
        std::cout << "ERROR: OBJ model not found at path: " << path << std::endl;
        exit(-1);
    }

    meshes.clear();

    std::vector<Vertex> curVertices;
    std::vector<unsigned int> curIndices;

    auto flushMesh = [&]()
    {
        if (!curVertices.empty())
        {
            Material mat;
            bool hasMat = false;

            if (!currentMaterialName.empty() &&
                materials.contains(currentMaterialName))
            {
                mat = materials[currentMaterialName];
                hasMat = true;
            }

            meshes.emplace_back(std::make_unique<Mesh>(
                curIndices,
                curVertices,
                std::vector<Texture>{},
                mat
                ));

            curVertices.clear();
            curIndices.clear();
        }
    };

    std::string str;
    int line = 0;

    while (std::getline(file, str))
    {
        line++;

        if (str.empty() || str.starts_with("#"))
        {
            continue;
        }

        if (str.starts_with("o ") || str.starts_with("g "))
        {
            if (!curIndices.empty())
                flushMesh();

            continue;
        }

        if (str.starts_with("mtllib "))
        {
            std::string mtlFile = str.substr(7);
            materials = MaterialLoader::loadMTL(Utils::getDirectory(path) + "/" + mtlFile, Utils::getDirectory(path));
            continue;
        }

        if (str.starts_with("usemtl "))
        {
            if (!curIndices.empty())
                flushMesh();

            currentMaterialName = str.substr(7);
            continue;
        }

        if (str.starts_with("v "))
        {
            glm::vec3 pos;
            if (sscanf(str.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z) == 3)
            {
                temp_positions.push_back(pos);
            }
            continue;
        }

        if (str.starts_with("vt "))
        {
            glm::vec2 uv;
            float w;
            int params = sscanf(str.c_str(), "vt %f %f %f", &uv.x, &uv.y, &w);
            if (params >= 2)
                temp_uvs.push_back(uv);
            continue;
        }

        if (str.starts_with("vn "))
        {
            glm::vec3 n;
            if (sscanf(str.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z) == 3)
                temp_normals.push_back(n);
            continue;
        }

        if (str.starts_with("f "))
        {
            std::string faceLine = str.substr(2);

            std::vector<std::string> tokens;
            {
                std::stringstream ss(faceLine);
                std::string tok;
                while (ss >> tok)
                    tokens.push_back(tok);
            }

            if (tokens.size() < 3)
            {
                std::cout << "ERROR: invalid face at line " << line << std::endl;
                continue;
            }

            for (int i = 1; i < tokens.size() - 1; ++i)
            {
                std::string tri[3] = {tokens[0], tokens[i], tokens[i + 1]};

                for (int k = 0; k < 3; ++k)
                {
                    FaceIndex fi = parseFaceLine(tri[k]);

                    Vertex v{};

                    int pos = fi.v - 1;
                    int uv = fi.vt - 1;
                    int nor = fi.vn - 1;

                    v.position = (pos >= 0 && pos < temp_positions.size()) ? temp_positions[pos] : glm::vec3(0);
                    v.uv = (uv >= 0 && uv < temp_uvs.size()) ? temp_uvs[uv] : glm::vec2(0);
                    v.normal = (nor >= 0 && nor < temp_normals.size()) ? temp_normals[nor] : glm::vec3(0, 1, 0);

                    v.color = glm::vec4(1.0);

                    curIndices.push_back(curVertices.size());
                    curVertices.push_back(v);
                }
            }
        }
    }

    flushMesh();
}

FaceIndex Model::parseFaceLine(std::string line)
{
    FaceIndex fi = {-1, -1, -1};

    if (line.find('/') != std::string::npos)
    {
        int v = 0, vt = 0, vn = 0;

        if (sscanf(line.c_str(), "%d/%d/%d", &v, &vt, &vn) == 3)
        {
            fi.v = v;
            fi.vt = vt;
            fi.vn = vn;
        }
        else if (sscanf(line.c_str(), "%d//%d", &v, &vn) == 2)
        {
            fi.v = v;
            fi.vn = vn;
        }
        else if (sscanf(line.c_str(), "%d/%d", &v, &vt) == 2)
        {
            fi.v = v;
            fi.vt = vt;
        }
    }
    else
    {
        fi.v = std::stoi(line);
    }

    return fi;
}

void Model::render(Shader &shader, const glm::mat4& model)
{
    for (int i = meshes.size() - 1; i >= 0; i--)
    {

        Mesh &mesh = *meshes.at(i);

        shader.use();
        
        mesh.render(shader, model);
    }
}