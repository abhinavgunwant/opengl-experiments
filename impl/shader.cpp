#include "../headers/shader.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader() {}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	init(vertexShaderPath, fragmentShaderPath);
}

void Shader::init(const char* vertexShaderPath, const char* fragmentShaderPath) {
	string vertexShaderCode;
	string fragmentShaderCode;

	ifstream vShaderFile;
	ifstream fShaderFile;

	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);

		stringstream vShaderStream;
		stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vertexShaderCode = vShaderStream.str();
		fragmentShaderCode = fShaderStream.str();

		vShaderFile.close();
		fShaderFile.close();
	} catch (ifstream::failure e) {
		cerr << "\nError reading shader files: " << e.what();
	}

	link(
		compile(SHADER_TYPE_VERTEX_SHADER, vertexShaderCode.c_str()),
		compile(SHADER_TYPE_FRAGMENT_SHADER, fragmentShaderCode.c_str())
	);
}

inline uint32_t Shader::compile(ShaderType type, const char* code) {
	uint32_t shaderID = 0;

	switch (type) {
		case SHADER_TYPE_VERTEX_SHADER: {
			shaderID = glCreateShader(GL_VERTEX_SHADER);
			break;
		}

		case SHADER_TYPE_FRAGMENT_SHADER: {
			shaderID = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
	}

	if (shaderID == 0) {
		cerr << "\nError: Could not create shader!";
		return 0;
	}

	int success;

	glShaderSource(shaderID, 1, (char const* const*)&code, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		char log[1024];
		glGetShaderInfoLog(shaderID, 1024, NULL, log);
		cerr << "\nError: vertexShader(" << shaderID << ")'s compilation failed:\n" << log;
	}

	return shaderID;
}

inline void Shader::link(uint32_t vertexShader, uint32_t fragmentShader) {
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	cout << "\nLinking... Program ID: " << programID;

	int success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success) {
		char log[1024];
		glGetProgramInfoLog(programID, 1024, NULL, log);
		cerr << "\nError while linking shader program:\n" << log;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(programID);
}

int Shader::getVariableIndex(const char* var) {
	return glGetUniformLocation(programID, var);
}

void Shader::setBool(int id, bool b) {
	if (id > 0) {
		glUniform1i(id, (int) b);
	}
}

void Shader::setInt(int id, int a) {
	if (id > 0) {
		glUniform1i(id, a);
	}
}

void Shader::setFloat(int id, float f) {
	if (id >= 0) {
		glUniform1f(id, f);
	} else {
		//cout << "\n!!!!" << id;
	}
}
