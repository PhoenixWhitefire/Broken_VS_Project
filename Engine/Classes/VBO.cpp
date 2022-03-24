#include"VBO.h"

VBO::VBO() {
	glGenBuffers(1, &this->ID);
}

void VBO::SetBufferData(std::vector<Vertex>& Vertices) {
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Destroy() {
	glDeleteBuffers(1, &this->ID);
}
