#ifndef GL_SHADERPROGRAM
#define GL_SHADERPROGRAM

#include"Debug.h"

#include<glad/glad.h>

#include"FileIO.h"

class ShaderProgram {
	public:
		ShaderProgram(std::string VertexShaderPath, std::string FragmentShaderPath);
		~ShaderProgram();

		void PrintErrors(unsigned int Object, const char* Type);

		void Activate();

		GLuint ID;
};

#endif
