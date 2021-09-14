#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Util.hpp"
#include "DrawTest01.hpp"

//响应键盘输入事件
//ESC推出窗口
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}




int main() {
    DrawTriangleAndRectangle(processInput,framebuffer_size_callback);
    return 0;
}