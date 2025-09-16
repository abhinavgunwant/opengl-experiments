#include <iostream>
#include <cstdlib>

#include "../headers/window-utils.hpp"

using namespace std;

GLFWwindow* createWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Experiments", NULL, NULL);

	if (window == NULL) {
		cout << "\nFailed to create GLFW window";
		glfwTerminate();
		exit(-1);
	}

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void init(GLFWwindow* window, GLFWframebuffersizefun resize_callback) {
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "\nFailed to initialize GLAD";
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	if (resize_callback == NULL) {
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	} else {
		glfwSetFramebufferSizeCallback(window, resize_callback);
	}

	glClearColor(0, 0, 0, 1.0);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
