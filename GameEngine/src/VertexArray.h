#pragma once

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void Bind() const;
};