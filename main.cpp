#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Util.hpp"

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
    //定义顶点与片源着色器的函数字符串
    std::string vsh1 =
            Util::readStringFromText(R"(C:\Users\Administrator\CLionProjects\GLFWLearning\Shaders\shader1.vsh)");
    //第一个片源着色器代码
    std::string fsh1 =
            Util::readStringFromText(R"(C:\Users\Administrator\CLionProjects\GLFWLearning\Shaders\shape1.fsh)");
    //第二个片源着色器代码
    //赋予不同的颜色
    std::string fsh2 =
            Util::readStringFromText(R"(C:\Users\Administrator\CLionProjects\GLFWLearning\Shaders\shape2.fsh)");
    const char* vertexShaderSource = vsh1.c_str();
    const char* fragmentShaderSource = fsh1.c_str();
    const char* fragmentShaderSource01 =fsh2.c_str();
    if(!glfwInit()) {
        std::cout << "failed" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800,600,"vsh1", nullptr, nullptr);
    if(!window){
        std::cout << "failed" << std::endl;
        glfwTerminate();
        return -2;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -3;
    }

    //构建和编译Shader

    //顶点Shader
    //创建顶点着色器对象
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //着色器源码附加到对象上，然后编译
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // 检查是否编译成功
    int success; //int 类型标识是否成功
    char infoLog[512];//储存错误消息的容器
    //glGetShaderiv（）检查是否编译成功
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        //glGetShaderInfoLog（）获取错误消息，然后打印它。
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    //片源Shader
    //创建第一个片源着色器对象
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    ////着色器源码附加到对象上，然后编译
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // 检查是否编译成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //创建第二个片源着色器对象
    int fragmentShader01 = glCreateShader(GL_FRAGMENT_SHADER);
    ////着色器源码附加到对象上，然后编译
    glShaderSource(fragmentShader01, 1, &fragmentShaderSource01, nullptr);
    glCompileShader(fragmentShader01);
    // 检查是否编译成功
    glGetShaderiv(fragmentShader01, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader01, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //链接Shader，链接顶点与片源
    //创建第一个链接对象
    int shaderProgram = glCreateProgram();
    //着色器附加到了程序上，然后用glLinkProgram链接
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //检查是否链接出错
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //把着色器对象链接到程序对象以后，删除着色器对象，不再需要它们
    //glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //创建链接第二个着色器
    int shaderProgram01 = glCreateProgram();
    //着色器附加到了程序上，然后用glLinkProgram链接
    glAttachShader(shaderProgram01, vertexShader);
    glAttachShader(shaderProgram01, fragmentShader01);
    glLinkProgram(shaderProgram01);

    //检查是否链接出错
    glGetProgramiv(shaderProgram01, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram01, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //把着色器对象链接到程序对象以后，删除着色器对象，不再需要它们
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader01);

    //设置顶点数据和顶点属性和索引
    float vertices01[] = {
            // 第一个四边形
            0.1f, 0.9f, 0.0f,
            0.9f, 0.9f, 0.0f,
            0.9f, 0.1f, 0.0f,
            0.1f, 0.1f, 0.0f,
            };
    //索引
    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };
    float vertices02[] = {
            // 第二个三角形
            -0.5f, 0.9f, 0.0f,
            -0.1f, 0.1f, 0.0f,
            -0.9f, 0.1f, 0.0f,
            };

    //创建 VBO 顶点缓冲对象 VAO顶点数组对象 EBO索引缓冲对象
    //多个对象
    unsigned int VBOs[2], VAOs[2], EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(1, &EBO);

    //第一个
    //绑定VAO,VBO与EBO对象
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //复制顶点数据到缓冲内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices01), vertices01, GL_STATIC_DRAW);

    // 赋值顶点索引到缓冲内存中
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //链接顶点属性，设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),nullptr);
    //以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
    glEnableVertexAttribArray(0);


    //第二个
    //绑定第二个VAO,VBO与EBO对象
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);


    //复制顶点数据到缓冲内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices02), vertices02, GL_STATIC_DRAW);

    //链接顶点属性，设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    //以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
    glEnableVertexAttribArray(0);

    /*******************************************渲染循环************************************************/



    //glfwWindowShouldClose()检查窗口是否需要关闭。如果是，游戏循环就结束了，接下来我们将会清理资源，结束程序
    while(!glfwWindowShouldClose(window)){
        //响应键盘输入
        processInput(window);

        //设置清除颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //清除当前窗口，把颜色设置为清除颜色
        glClear(GL_COLOR_BUFFER_BIT);

        //激活链接程序，激活着色器，开始渲染
        glUseProgram(shaderProgram);
        //绑定VAO
        glBindVertexArray(VAOs[0]);
        //绘制四边形
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        //绘制第二个三角形
        glUseProgram(shaderProgram01);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //线框绘制
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //交换颜色缓冲
        glfwSwapBuffers(window);
        //处理事件
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}