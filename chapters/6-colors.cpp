/**
 * https://learnopengl.com/Lighting/Colors
 */

#include "6-colors.hpp"

#include <iostream>
#include <direct.h>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../lib/stb_image.h"
#include "../headers/window-utils.hpp"
#include "../headers/shader.hpp"
#include "../headers/camera.hpp"

bool ch6_firstMouse = true;

float ch6_lastX;
float ch6_lastY;
float ch6_prevTime = 0.0f;

Camera ch6_camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -80.0f, 0.0f);

void ch6_procInput(GLFWwindow * window) {
    const float cameraSpeed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        exit(0);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        ch6_camera.processKeyboard(BACKWARD, ch6_prevTime - glfwGetTime());
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        ch6_camera.processKeyboard(FORWARD, ch6_prevTime - glfwGetTime());
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        ch6_camera.processKeyboard(RIGHT, ch6_prevTime - glfwGetTime());
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        ch6_camera.processKeyboard(LEFT, ch6_prevTime - glfwGetTime());
    }
}

void ch6_mouseCallback(GLFWwindow * window, double xpos, double ypos) {
    if (ch6_firstMouse) {
        ch6_lastX = xpos;
        ch6_lastY = ypos;
        ch6_firstMouse = false;
    }

    float xoffset = xpos - ch6_lastX;
    float yoffset = ch6_lastY - ypos;

    ch6_lastX = xpos;
    ch6_lastY = ypos;

    ch6_camera.processMouseMovement(xoffset, yoffset);
}

void ch6_scrollCallback(GLFWwindow * window, double xoffset, double yoffset) {
    ch6_camera.processMouseScroll(yoffset);
}

void chapter6() {
	GLFWwindow* window = createWindow();

	init(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, ch6_mouseCallback);
    glfwSetScrollCallback(window, ch6_scrollCallback);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

	uint32_t indices[] = { 1, 2, 0, 3 };
	int success;
	char log[1024];
	uint32_t VAO;
    uint32_t lightVAO;
	uint32_t VBO;
	uint32_t EBO;
	uint32_t texture[2];

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

	Shader shader("./shaders/6.vert", "./shaders/6.frag");
    Shader lightShader("./shaders/6.vert", "./shaders/6-light-cube.frag");

	// Load texture image
	glGenTextures(2, texture);

    // Coordinate transformations
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

	// Transformation
	glm::mat4 transform;

	int texture1Uniform = shader.getVariableIndex("texture1");
	int texture2Uniform = shader.getVariableIndex("texture2");
	// int transformUniform = shader.getVariableIndex("transform");
    int modelUniform = shader.getVariableIndex("modelMatrix");
    int viewUniform = shader.getVariableIndex("viewMatrix");
    int projectionUniform = shader.getVariableIndex("projectionMatrix");
    int objectColorUniform = shader.getVariableIndex("objectColor");
    int lightColorUniform = shader.getVariableIndex("lightColor");
    int modelUniform2 = lightShader.getVariableIndex("modelMatrix");
    int viewUniform2 = lightShader.getVariableIndex("viewMatrix");
    int projectionUniform2 = lightShader.getVariableIndex("projectionMatrix");

	shader.use();

    glUniform3f(objectColorUniform, 1.0f, 0.5f, 0.31f);
    glUniform3f(lightColorUniform, 1.0f, 1.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		ch6_procInput(window);

        viewMatrix = ch6_camera.getViewMatrix();

        projectionMatrix = glm::perspective(glm::radians(ch6_camera.Zoom), 1.0f, 0.1f, 100.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);

        shader.use();

        modelMatrix = glm::mat4(1.0f);
        glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(lightVAO);

        lightShader.use();

        modelMatrix = glm::scale(
            glm::translate(glm::mat4(1.0f), glm::vec3(1.2f, 1.0f, 2.0f)),
            glm::vec3(0.2f)
        );
        glUniformMatrix4fv(modelUniform2, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewUniform2, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionUniform2, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        ch6_prevTime = glfwGetTime();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

