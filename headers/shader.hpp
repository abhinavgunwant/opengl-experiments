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
		uint32_t compile(ShaderType type, const char* code);
		void link(uint32_t vertexShader, uint32_t fragmentShader);

	public:
		uint32_t programID;

		Shader();
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

		void use();
		void init(const char* vertexShaderPath, const char* fragmentShaderPath);

		int getVariableIndex(const char* var);

		void setBool(int varId, bool b);
		void setInt(int varId, int a);
		void setFloat(int varId, float f);
};

#endif // OPENGL_EXPERIMENTS_SHADER
