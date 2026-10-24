#include "Renderer.h"

#include <iostream>

#include <string>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Window.h"

int main(void)
{
    Window window(640, 480, "Hello World");

    float positions[] = {
        0.0f, 0.0f, -0.5f, // 0
        0.0f, 0.5f, -0.5f, // 1
        0.5f, 0.5f, -0.5f, // 2
        0.5f, 0.0f, -0.5f, // 3
        0.0f, 0.0f,  0.0f, // 4
        0.0f, 0.5f,  0.0f, // 5
        0.5f, 0.5f,  0.0f, // 6
        0.5f, 0.0f,  0.0f  // 7
    };

    unsigned int indices[] = {
        0, 1, 2,  2, 3, 0, // Back
        4, 6, 5,  6, 4, 7, // Front
        0, 4, 5,  5, 1, 0, // Left
        3, 2, 6,  6, 7, 3, // Right
        1, 5, 6,  6, 2, 1, // Top
        0, 3, 7,  7, 4, 0  // Bottom
    };

    VertexArray vao;
    vao.Bind();

    VertexBuffer vbo(positions, sizeof(positions));
    IndexBuffer ibo(indices, sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    Shader shader("./res/shaders/vert.glsl", "./res/shaders/frag.glsl");

    while (window.IsOpen())
    {
        window.Clear();

        shader.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        window.Update();
    }

    return 0;
}