#include"Texture.h"

Texture::Texture(const char* TexturePath, const char* TextureType, GLuint TextureSlot, GLenum ImageFormat) {
	this->Type = TextureType;

	this->Slot = TextureSlot;

	int ImageWidth, ImageHeight, ImageColorChannels;

	//stb reads images differently from OpenGL (top-left to bottom-right and bottom-left to top-right respectively)
	stbi_set_flip_vertically_on_load(true);

	unsigned char* ImageData = stbi_load(TexturePath, &ImageWidth, &ImageHeight, &ImageColorChannels, 0);

	if (ImageData == nullptr) {
		printf("Failed to load texture file: %s\n", TexturePath);

		Debug::ShowPrompt("Engine error", "stbi failed to load image data", MB_YESNO, true);
	}

	glGenTextures(1, &this->ID);
	glActiveTexture(GL_TEXTURE0 + TextureSlot);
	glBindTexture(GL_TEXTURE_2D, this->ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, ImageFormat, GL_UNSIGNED_BYTE, ImageData);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(ImageData);
	
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0 + this->Slot);
}

void Texture::TexUnit(ShaderProgram* Shaders, const char* UniformName, GLuint Unit) {
	GLuint Uniform = glGetUniformLocation(Shaders->ID, UniformName);

	Shaders->Activate();
	
	glUniform1i(Uniform, Unit);
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + this->Slot);
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Destroy() {
	glDeleteTextures(1, &this->ID);
}
