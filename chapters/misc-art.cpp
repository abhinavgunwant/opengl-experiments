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

void art() {
	GLFWwindow* window = createWindow();
	init(window);

	float vertices[] = {
		-1, -1, 0, 1, 0, 0,
		1, -1, 0, 0, 1, 0,
		1, 1, 0, 0, 0, 1,
		-1, 1, 0, 0, 0, 0,
	};

	uint32_t indices[] = { 1, 2, 0, 3 };

	int success;
	char log[1024];
	uint32_t VAO;
	uint32_t VBO;
	uint32_t EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	uint8_t fpsCounter = 0;
	float time = 0;
	uint32_t prevFrameTime = 0;
	float opacity;

	Shader art("./shaders/colorbox.vert", "./shaders/art.frag");

	int resolutionUniform = art.getVariableIndex("resolution");
	int opacityUniform = art.getVariableIndex("opacity");
	int timeUniform = art.getVariableIndex("time");

	while (!glfwWindowShouldClose(window)) {
		++fpsCounter;
		time = glfwGetTime();

		opacity = (sin(time * 8) + 1) / 2;

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		art.use();
		glUniform2f(resolutionUniform, 800, 800);
		art.setFloat(opacityUniform, opacity);
		art.setFloat(timeUniform, time);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

		if ((uint32_t)time > prevFrameTime) {
			cout << "\nFPS: " << (int)fpsCounter;
			fpsCounter = 0;
			++prevFrameTime;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
