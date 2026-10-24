#pragma once

#include <string>

class Shader
{
private:
	unsigned int m_RendererID;

public:
	Shader(std::string vertexShaderFilepath, std::string fragmentShaderFilepath);
	~Shader();

	void Bind() const;
};