/**
 * Inspired by: https://learnopengl.com/In-Practice/Text-Rendering
 **/

#ifndef OPENGL_EXPERIMENT_TEXT
#define OPENGL_EXPERIMENT_TEXT

#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.hpp"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	glm::ivec2   size;      // Size of glyph
	glm::ivec2   bearing;   // Offset from baseline to left/top of glyph
	unsigned int textureID; // ID handle of the glyph texture
	unsigned int advance;   // Horizontal offset to advance to next glyph
};

extern Character Characters[128];
extern Shader textShader;
extern unsigned int VAO, VBO;

void initCharGlyph(FT_Face& face, unsigned char c);
void initFonts();
void initTextRendering();
void renderText(string text, float x, float y, glm::fvec3 color = glm::fvec3(1.0, 1.0, 1.0));

#endif // OPENGL_EXPERIMENT_TEXT
