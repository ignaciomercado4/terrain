#ifndef MODEL_HPP
#define MODEL_HPP

#include "./Mesh.hpp"
#include <string>

struct FaceIndex {
    int v, vt, vn;
};

class Model
{
private:
    std::vector<Mesh> meshes;
    void loadOBJ(std::string path);
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    FaceIndex parseFaceLine(std::string line);

public:
    Model(std::string path);
    void render(Shader &shader);
};

#endif