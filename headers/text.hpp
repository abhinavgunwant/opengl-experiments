#ifndef OPENGL_EXPERIMENT_TEXT
#define OPENGL_EXPERIMENT_TEXT

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>

#include "shader.hpp"

using namespace std;

struct Character {
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int textureID;
	unsigned int advance;
};

extern Character characters[128];
extern Shader textShader;
extern unsigned int textVAO;
extern unsigned int textVBO;

void initTextRendering();
void initFont();
void drawText(string text, float x, float y, float scale, glm::vec3 color);

#endif // OPENGL_EXPERIMENT_TEXT
