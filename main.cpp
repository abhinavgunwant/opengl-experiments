#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/window-utils.hpp"

using namespace std;

void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	GLFWwindow* window = createWindow();

	init(window);
	
	float vertices[] = {
		-0.5, -0.5f, 0, 1, 0, 0,
		0.5, -0.5f, 0, 0, 1, 0,
		0.5, 0.5f, 0, 0, 0, 1,
		-0.5, 0.5f, 0, 0, 0, 0,
	};

	uint32_t indices[] = { 1, 2, 0, 3 };

	int success;
	char log[1024];
	uint32_t VAO;
	uint32_t VBO;
	uint32_t EBO;
	uint32_t vertexShader;
	uint32_t fragmentShader;
	uint32_t shaderProgram;

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 sharedColor;"
		"uniform float time;"
		"void main() {"
			"float cosTheta = cos(time);"
			"float sinTheta = sin(time);"
			"float x = aPos.x * cosTheta - aPos.y * sinTheta;"
			"float y = aPos.x * sinTheta + aPos.y * cosTheta;"
			"gl_Position = vec4(x, y, 0, 1.0);"
			"sharedColor = aColor;"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;"
		"in vec3 sharedColor;"
		"uniform float opacity;"
		"void main() {"
			"float r = sharedColor.x * opacity;"
			"float g = sharedColor.y * opacity;"
			"float b = sharedColor.z * opacity;"
			"FragColor = vec4(r, g, b, 1);"
		"}\0";

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

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 1024, NULL, log);
		cout << "\nError: vertexShader(" << vertexShader << ")'s compilation failed:\n" << log;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 1024, NULL, log);
		cout << "\nError: fragmentShader(" << fragmentShader << ")'s compilation failed:\n" << log;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 1024, NULL, log);
		cout << "\nError: shaderProgram(" << shaderProgram << ")'s linking failed:\n" << log;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	uint8_t fpsCounter = 0;
	float time = 0;
	uint32_t prevFrameTime = 0;
	float opacity;

	uint32_t opacityUniform = glGetUniformLocation(shaderProgram, "opacity");
	uint32_t timeUniform = glGetUniformLocation(shaderProgram, "time");

	while (!glfwWindowShouldClose(window)) {
		++fpsCounter;
		time = glfwGetTime() * 64;

		opacity = (sin(time) + 1) / 2;
		//cout << "\nOpacity: " << opacity;

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glUniform1f(opacityUniform, opacity);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

		if ((uint32_t)time > prevFrameTime) {
			cout << "\nFPS: " << (int)fpsCounter;
			fpsCounter = 0;
			glUniform1f(timeUniform, time);
			++prevFrameTime;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glfwTerminate();
	return 0;
}
