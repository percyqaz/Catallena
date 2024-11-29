#include "catallena.h"
#include "render.h"
#include "callbacks.h"
#include <GLFW/glfw3.h>
#include "glad/gl.h"
#include <math.h>
#include <iostream>

using namespace Catallena;

int example_program()
{
    std::cout << "Hello World!\n";

    if (!glfwInit())
    {
        std::cout << "GLFW init failed :(\n";
        return 0;
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Catallena Window", NULL, NULL);

    if (!window)
    {
        std::cout << "GLFW window creation failed :(\n";
        return 0;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    Graphics::Render::init();
    Graphics::Render::resize(width, height);
    glfwSwapInterval(1); // vsync

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        GLenum error = glGetError();
        if (error)
        {
            std::cout << error << "\n";
        }

        Graphics::Render::start();
        Graphics::Render::rect({ 10.0f, 10.0f, 100.0f, 100.0f }, { 255, 0, 0, 255 });
        Graphics::Render::finish();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}