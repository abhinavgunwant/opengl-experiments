#ifndef OPENGL_EXPERIMENTS_SHADER
#define OPENGL_EXPERIMENTS_SHADER

#include <string>

enum ShaderType {
	SHADER_TYPE_VERTEX_SHADER,
	SHADER_TYPE_FRAGMENT_SHADER,
};

using namespace std;

class Shader {
	private:
		uint32_t programID;

		/** Always points to the next variable index */
		uint8_t latestVar;

		/** Stores all the variable names (max: 20) */
		char vars[20][20];

		uint32_t compile(ShaderType type, const char* code);
		void link(uint32_t vertexShader, uint32_t fragmentShader);

	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

		void use();

		int getVariableIndex(const char* var);

		void setInt(int varId, int a);
		void setFloat(int varId, float f);
};

#endif // OPENGL_EXPERIMENTS_SHADER
