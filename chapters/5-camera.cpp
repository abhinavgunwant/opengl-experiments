/**
 * https://learnopengl.com/Getting-started/Camera
 */

#include "5-camera.hpp"

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

#define MOUSE_SENSITIVITY 0.1f;

bool cameraAnimation = false;
bool spacePressed = false;
bool firstMouse = true;

float lastX;
float lastY;
float pitch = 0.0f;
float yaw = 0.0f;
float fov = 45.0f;
float prevTime = 0.0f;

// Camera
const glm::vec3 DEFAULT_CAMERA_POS = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraPos = DEFAULT_CAMERA_POS;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraPosPrev;

Camera camera(cameraPos, cameraUp, -90.0f, 0.0f);

void procInput(GLFWwindow * window) {
    const float cameraSpeed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        exit(0);
    }

    if (!spacePressed && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        spacePressed = true;
    }

    if (spacePressed && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        cameraAnimation = !cameraAnimation;

        if (cameraAnimation) {
            cameraPosPrev = cameraPos;
            cameraPos = DEFAULT_CAMERA_POS;
            cout << "\nPlaying camera animation";
            spacePressed = false;
            return;
        } else {
            cameraPos = cameraPosPrev;
            cout << "\nPausing camera animation";
            spacePressed = false;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(BACKWARD, prevTime - glfwGetTime());
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(FORWARD, prevTime - glfwGetTime());
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(RIGHT, prevTime - glfwGetTime());
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(LEFT, prevTime - glfwGetTime());
    }
}

void mouseCallback(GLFWwindow * window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow * window, double xoffset, double yoffset) {
    camera.processMouseScroll(yoffset);
}

void chapter5() {
	GLFWwindow* window = createWindow();

	init(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
	uint32_t VBO;
	uint32_t EBO;
	uint32_t texture[2];

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

	Shader shader("./shaders/4.vert", "./shaders/4.frag");

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

    // Coordinate transformations
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // Camera
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 viewMatrix; // View matrix is the camera's "Look At" matrix.
    glm::mat4 projectionMatrix;

	// Transofrmation
	glm::mat4 transform;

	int texture1Uniform = shader.getVariableIndex("texture1");
	int texture2Uniform = shader.getVariableIndex("texture2");
	// int transformUniform = shader.getVariableIndex("transform");
    int modelUniform = shader.getVariableIndex("modelMatrix");
    int viewUniform = shader.getVariableIndex("viewMatrix");
    int projectionUniform = shader.getVariableIndex("projectionMatrix");

	shader.use();

	glUniform1i(texture1Uniform, 0);
	glUniform1i(texture2Uniform, 1);

    float time;
    float rotation = 0.0f;
    const float radius = 10.0f;

	while (!glfwWindowShouldClose(window)) {
		procInput(window);

        time = (float) glfwGetTime();

        if (cameraAnimation) {
            cameraPos.x = sin(time) * radius;
            cameraPos.z = cos(time) * radius;
            viewMatrix = glm::lookAt(cameraPos, cameraTarget, cameraUp);
        } else {
            viewMatrix = camera.getViewMatrix();
        }

        projectionMatrix = glm::perspective(glm::radians(camera.Zoom), 1.0f, 0.1f, 100.0f);

        rotation = glm::radians(time);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

        glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		glBindVertexArray(VAO);

        for (uint8_t i=0; i<10; ++i) {
            modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
            float angle = rotation * (i + 1);
            modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        prevTime = time;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

