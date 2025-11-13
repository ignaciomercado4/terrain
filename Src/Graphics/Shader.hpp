#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <glm/glm.hpp>
#include "./GLObject.hpp"

class Shader : public GLObject
{
private:
    unsigned int ID;
    void checkCompileErrors(unsigned int shader, std::string type);

public:
    Shader(std::string VSPath, std::string FSPath);
    void bind() override;
    void unbind() override;
    ~Shader();
    void use();
    unsigned int getID();

    // Uniform methods
    void setMat4(glm::mat4 m, std::string name);
    void setInt(int i, std::string name);
    void setVec3(glm::vec3 v, std::string name);
};

#endif