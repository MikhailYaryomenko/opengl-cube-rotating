#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

class Shader
{
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(std::string vertexShaderFilepath, std::string fragmentShaderFilepath);
	~Shader();

	void Bind() const;

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	int GetUniformLocation(const std::string& name);
};