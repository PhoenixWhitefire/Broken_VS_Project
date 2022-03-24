#ifndef CLASS_TEXTURE
#define CLASS_TEXTURE

#include"ShaderProgram.h"

#include<glad/glad.h>
#include<stb/stb_image.h>

class Texture {
	public:
		GLuint ID;
		const char* Type;
		GLuint Slot;

		Texture(const char* TexturePath, const char* TextureType, GLuint TextureSlot, GLenum ImageFormat);

		void TexUnit(ShaderProgram* Shaders, const char* UniformName, GLuint Unit);

		void Bind();
		void Unbind();
		void Destroy();
};

#endif

