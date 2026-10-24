#pragma once

#include "Renderer.h"

class Window
{
private:
    GLFWwindow* m_Window;
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool IsOpen() const;
    void Update();
    void Clear();
};
