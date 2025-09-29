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
#include "chapters/2-textures.hpp"
#include "chapters/3-transformations.hpp"
#include "chapters/4-coordinate-systems.hpp"
#include "chapters/5-camera.hpp"
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
		cout << "\nMenu:\n\n  1. Chapter 1: Hello Triangle\n  2. Chapter 2: Textures\n  3. Chapter 3: Transformations\n  4. Chapter 4: Coordinate Systems\n  5. Camera"
            << "\n  6. Art Shader\n  7. Text rendering\nEnter your response: ";
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
		case 2: chapter2(); break;
		case 3: chapter3(); break;
		case 4: chapter4(); break;
        case 5: chapter5(); break;
        case 6: art(); break;
		case 7: text_rendering(); break;
	}

	return 0;
}
