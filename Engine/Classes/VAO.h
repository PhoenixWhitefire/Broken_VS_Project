#ifndef CLASS_VAO
#define CLASS_VAO

#include"VBO.h"

class VAO {
public:
	VAO();

	void LinkAttrib(VBO& VertexBuffer, GLuint Layout, GLuint Components, GLenum Type, GLsizei Stride, void* Offset);

	void Bind();
	void Unbind();
	void Destroy();

	GLuint ID;
};

#endif
