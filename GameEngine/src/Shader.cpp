#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"

std::string getShaderContent(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Failed to open shader source file: " << filepath << std::endl;
    }
    std::stringstream source;
    source << file.rdbuf();
    std::string fileContent = source.str();

    return fileContent;
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

Shader::Shader(std::string vertexShaderFilepath, std::string fragmentShaderFilepath)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderContent = getShaderContent(vertexShaderFilepath);
    const char* vertexShaderSource = vertexShaderContent.c_str();

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderContent = getShaderContent(fragmentShaderFilepath);
    const char* fragmentShaderSource = fragmentShaderContent.c_str();

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    m_RendererID = program;
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}
