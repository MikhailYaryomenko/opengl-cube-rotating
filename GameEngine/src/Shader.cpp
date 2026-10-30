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
    : m_RendererID(0)
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

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}
