#ifndef OPENGL_EXPERIMENTS_WINDOW_UTILS
#define OPENGL_EXPERIMENTS_WINDOW_UTILS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* createWindow();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void init(GLFWwindow* window);
void processInput(GLFWwindow* window);

#endif // OPENGL_EXPERIMENTS_WINDOW_UTILS
