#include"Render3D.h"

Render3D::Render3D(Window* Window) {
	this->CurrentWindow = Window;

	this->VertexArray = new VAO();
	this->VertexArray->Bind();

	this->VertexBuffer = new VBO();
	this->ElementBuffer = new EBO();

	this->VertexArray->LinkAttrib(*this->VertexBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	this->VertexArray->LinkAttrib(*this->VertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	this->VertexArray->LinkAttrib(*this->VertexBuffer, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	this->VertexArray->LinkAttrib(*this->VertexBuffer, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
}

//void Render3D::DrawVerts(
//	GLfloat Vertices[],
//	GLuint Indices[],
//	int IndicesLength,
//	Vector3 Position,
//	Vector3 Size,
//	ShaderProgram* Shaders
//) {
//
//}

void Render3D::Draw(
	Mesh* Object, //TODO: figure out if pointers use less memory than passing around a value
	Vector3 Position, Vector3 Size,
	ShaderProgram* Shaders
) {
	Render3D::VertexArray->Bind();
	Render3D::VertexBuffer->Bind();
	Render3D::ElementBuffer->Bind();

	Render3D::VertexBuffer->SetBufferData(Object->Vertices);
	Render3D::ElementBuffer->SetBufferData(Object->Indices);

	this->VertexArray->Unbind();
	this->VertexBuffer->Unbind();
	this->ElementBuffer->Unbind();

	this->VertexArray->Bind();

	glUniform3f(glGetUniformLocation(Shaders->ID, "Size"), Size.X, Size.Y, Size.Z);

	glUniform3f(glGetUniformLocation(Shaders->ID, "Position"), Position.X, Position.Y, Position.Z);

	glDrawElements(GL_TRIANGLES, Object->Indices.size(), GL_UNSIGNED_INT, 0);

	this->VertexArray->Unbind();
	this->VertexBuffer->Unbind();
	this->ElementBuffer->Unbind();
}

