#ifndef MODEL_HPP
#define MODEL_HPP

#include "./Mesh.hpp"
#include <string>
#include <memory>

struct FaceIndex
{
    int v, vt, vn;
};

class Model
{
private:
    std::vector<std::unique_ptr<Mesh>> meshes;
    void loadOBJ(std::string path);
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    FaceIndex parseFaceLine(std::string line);
    std::map<std::string, Material> materials; 
    std::string currentMaterialName = "";      

public:
    Model(std::string path);
    void render(Shader &shader, const glm::mat4 &model = glm::mat4(1.0f));
};

#endif