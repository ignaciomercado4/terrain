#ifndef MODEL_HPP
#define MODEL_HPP

#include "./Mesh.hpp"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "./Shader.hpp"

class Model
{
private:
    std::vector<Mesh> meshes;
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
    std::string directory;
    std::vector<Texture> loadedTextures;

public:
    void render(Shader& shader);
    Model(std::string path);
};

#endif