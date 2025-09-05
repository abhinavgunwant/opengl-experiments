/**
 * - https://learnopengl.com/Getting-started/Transformations
 */
#include "3-transformations.hpp"

#include <iostream>
#include <cmath>
#include <direct.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../lib/stb_image.h"
#include "../headers/window-utils.hpp"
#include "../headers/shader.hpp"
#include "../headers/text.hpp"

void chapter3() {
	GLFWwindow* window = createWindow();

	init(window);

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	uint32_t indices[] = { 1, 2, 0, 3 };
	int success;
	char log[1024];
	uint32_t VAO;
	uint32_t VBO;
	uint32_t EBO;
	uint32_t texture[2];

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Shader shader("./shaders/3.vert", "./shaders/3.frag");

	// Load texture image
	glGenTextures(2, texture);

	string textureLocation[] = {
		"assets/textures/container.jpg",
		"assets/textures/awesomeface.png",
	};

	for (uint8_t i = 0; i < 2; ++i) {
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;

		stbi_set_flip_vertically_on_load(true);

		uint8_t* data = stbi_load(textureLocation[i].c_str(), &width, &height, &nrChannels, 0);

		if (data) {
			cout << "\nTexture " << textureLocation[i] << " loaded.";
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, i == 1 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			cout << "\nFailed to load texture.";
		}

		stbi_image_free(data);
	}

	// Transofrmation
	glm::mat4 transform;

	int texture1Uniform = shader.getVariableIndex("texture1");
	int texture2Uniform = shader.getVariableIndex("texture2");
	int transformUniform = shader.getVariableIndex("transform");

	shader.use();

	glUniform1i(texture1Uniform, 0);
	glUniform1i(texture2Uniform, 1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		transform = glm::translate(glm::mat4(1), glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0, 0, 1.0));
		glUniformMatrix4fv(transformUniform, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
