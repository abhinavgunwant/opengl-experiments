#include "misc-art.hpp"

#include <iostream>
#include <cmath>
#include <direct.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../headers/window-utils.hpp"
#include "../headers/shader.hpp"
#include "../headers/text.hpp"

using namespace std;

void text_rendering() {
	GLFWwindow* window = createWindow();
	init(window);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initTextRendering();

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		renderText("Abhinav's text rendering attempt", 10, 750, glm::fvec3(1.0, 0, 0));
		renderText("In", 10, 700, glm::fvec3(0, 1.0, 0));
		renderText("OpenGL", 10, 650, glm::fvec3(0, 0, 1.0));
		renderText("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 15.0f, 15.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
