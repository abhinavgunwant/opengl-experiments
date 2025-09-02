#include <iostream>
#include <cmath>
#include <direct.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "headers/window-utils.hpp"
#include "headers/shader.hpp"
#include "headers/text.hpp"
#include "chapters/1-hello_triangle.hpp"
#include "chapters/misc-art.hpp"
#include "chapters/misc-text-rendering.hpp"

using namespace std;

int main(int argCount, char ** args) {
	cout << "argCount: " << argCount;

	for (int i = 0; i < argCount; i++) {
		cout << "\nArg: " << args[i];
	}

	int response;

	if (argCount < 2) {
		cout << "\nMenu:\n\n  1. Chapter 1: Hello Triangle\n  2. Art Shader\n  3. Text rendering\nEnter your response: ";
		cin >> response;
	} else {
		response = atoi(args[1]);
	}

	char *cwd;

	if ((cwd = _getcwd(NULL, 0)) == NULL) {
		cerr << "\nError getting cwd";
	} else {
		cout << "\nCurrent working directory: " << cwd;
	}

	switch (response) {
		default:
		case 1:	chapter1(); break;
		case 2: art(); break;
		case 3: text_rendering(); break;
	}
	return 0;
}
