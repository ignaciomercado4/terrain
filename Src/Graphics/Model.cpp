#include "./Model.hpp"
#include "./Mesh.hpp"
#include "../Misc/Globals.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

Model::Model(std::string path)
{
    loadOBJ(path);
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

    std::string str;
    int line = 0;
    std::vector<Vertex> finalVertices;
    std::vector<unsigned int> finalIndices;
    while (std::getline(file, str))
    {
        line++;
        // ignore comments and empty lines
        if (str.empty() || str.starts_with("#"))
            continue;

        // vertex
        if (str.starts_with("v "))
        {
            glm::vec3 pos;
            int params = sscanf(str.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
            if (params >= 3)
            {
                temp_positions.push_back(pos);
            }
            else
            {
                std::cout << "WARNING: invalid v line " << "(" << line << ")" << "at model: " << path << std::endl;
            }
        }
        // vertex uv
        else if (str.starts_with("vt "))
        {
            glm::vec2 uv;
            float w;
            int params = sscanf(str.c_str(), "vt %f %f %f", &uv.x, &uv.y, &w);

            if (params >= 2)
            {
                temp_uvs.push_back(uv);
            }
            else
            {
                std::cout << "WARNING: invalid vt line " << "(" << line << ")" << "at model: " << path << std::endl;
            }
        }

        // vertex normals
        else if (str.starts_with("vn "))
        {
            glm::vec3 n;
            int params = sscanf(str.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z);

            if (params >= 3)
            {
                temp_normals.push_back(n);
            }
            else
            {
                std::cout << "WARNING: invalid vn line " << "(" << line << ")" << "at model: " << path << std::endl;
            }
        }
        // face
        else if (str.starts_with("f "))
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
                std::cout << "ERROR: cara inválida en línea "
                          << line << ": " << str << std::endl;
                continue;
            }

            // Triangulación fan:
            // (0, i-1, i)
            for (int i = 1; i < tokens.size() - 1; ++i)
            {
                std::string tri[3] = {tokens[0], tokens[i], tokens[i + 1]};

                for (int k = 0; k < 3; ++k)
                {
                    FaceIndex fi = parseFaceLine(tri[k]);

                    int posIndex = fi.v > 0 ? fi.v - 1 : -1;
                    int uvIndex = fi.vt > 0 ? fi.vt - 1 : -1;
                    int norIndex = fi.vn > 0 ? fi.vn - 1 : -1;

                    Vertex vert{};

                    if (posIndex >= 0 && posIndex < temp_positions.size())
                        vert.position = temp_positions[posIndex];
                    else
                        vert.position = glm::vec3(0);

                    if (uvIndex >= 0 && uvIndex < temp_uvs.size())
                        vert.uv = temp_uvs[uvIndex];
                    else
                        vert.uv = glm::vec2(0);

                    if (norIndex >= 0 && norIndex < temp_normals.size())
                        vert.normal = temp_normals[norIndex];
                    else
                        vert.normal = glm::vec3(0, 1, 0);

                    vert.color = glm::vec4(1.0f);

                    finalIndices.push_back(finalVertices.size());
                    finalVertices.push_back(vert);
                }
            }
        }
    }
    meshes.clear();
    meshes.emplace_back(finalIndices, finalVertices, std::vector<Texture>{});
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

void Model::render(Shader &shader)
{
    for (auto &m : meshes)
    {
        m.render(shader);
    }
}