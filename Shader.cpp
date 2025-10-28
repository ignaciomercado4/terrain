#include "./Shader.hpp"
#include "./Utils.hpp"
#include <iostream>

Shader::Shader(std::string VSPath, std::string FSPath)
{
    std::string VSSource = Utils::loadFileContents(VSPath);
    const char *VSSource_ccp = VSSource.c_str();
    std::string FSSource = Utils::loadFileContents(FSPath);
    const char *FSSource_ccp = FSSource.c_str();

    unsigned int VSShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VSShader, 1, &VSSource_ccp, 0);
    glCompileShader(VSShader);
    Shader::checkCompileErrors(VSShader, "VERTEX_SHADER");

    unsigned int FSShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FSShader, 1, &FSSource_ccp, 0);
    glCompileShader(FSShader);
    Shader::checkCompileErrors(FSShader, "FRAGMENT_SHADER");

    ID = glCreateProgram();
    glAttachShader(ID, VSShader);
    glAttachShader(ID, FSShader);
    glLinkProgram(ID);
    Shader::checkCompileErrors(ID, "PROGRAM");
    glDeleteShader(VSShader);
    glDeleteShader(FSShader);
};

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Shader compilation error of type: " << type << "\n"
                      << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Shader linking error of type: " << type << "\n"
                      << infoLog << std::endl;
        }
    }
}

void Shader::bind()
{
    glUseProgram(ID);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::use()
{
    glUseProgram(ID);
}

unsigned int Shader::getID()
{
    return ID;
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::setMat4(glm::mat4 m, std::string name)
{
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        std::cerr << "ERROR: Unable to locate uniform (Mat4) named: " << name << "\n";
    } else
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
    }
}
