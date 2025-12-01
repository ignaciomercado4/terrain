#include "./Model.hpp"

Model::Model(std::string path)
{
    loadModel(path);
}

void Model::render(Shader& shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].render(shader);
    }
}


void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        // position
        vertex.position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        // normal
        if (mesh->HasNormals())
        {
            vertex.normal = {
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            };
        }

        // UV
        if (mesh->mTextureCoords[0])
        {
            vertex.uv = {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            };
        }
        else vertex.uv = {0.0f, 0.0f};

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    auto diffuse = loadMaterialTextures(material, aiTextureType_DIFFUSE);
    auto specular = loadMaterialTextures(material, aiTextureType_SPECULAR);
    auto normals = loadMaterialTextures(material, aiTextureType_NORMALS);

    textures.insert(textures.end(), diffuse.begin(), diffuse.end());
    textures.insert(textures.end(), specular.begin(), specular.end());
    textures.insert(textures.end(), normals.begin(), normals.end());

    return Mesh(vertices, indices, textures);
}


std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::string fullPath = directory + "/" + std::string(str.C_Str());

        Texture tex(fullPath);

        textures.push_back(tex);
    }

    return textures;
}
