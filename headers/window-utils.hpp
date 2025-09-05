#ifndef OPENGL_EXPERIMENTS_WINDOW_UTILS
#define OPENGL_EXPERIMENTS_WINDOW_UTILS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 800

GLFWwindow* createWindow();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void init(GLFWwindow* window, GLFWframebuffersizefun resize_callback = NULL);
void processInput(GLFWwindow* window);

#endif // OPENGL_EXPERIMENTS_WINDOW_UTILS
