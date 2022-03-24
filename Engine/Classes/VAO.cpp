#include"VAO.h"

#include<iostream>

VAO::VAO() {
	glGenVertexArrays(1, &this->ID);
}

void VAO::LinkAttrib(VBO& VertexBuffer, GLuint Layout, GLuint Components, GLenum Type, GLsizei Stride, void* Offset) {
	VertexBuffer.Bind();
	glVertexAttribPointer(Layout, Components, Type, GL_FALSE, Stride, Offset);
	glEnableVertexAttribArray(Layout);
	VertexBuffer.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(this->ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Destroy() {
	glDeleteVertexArrays(1, &this->ID);
}
