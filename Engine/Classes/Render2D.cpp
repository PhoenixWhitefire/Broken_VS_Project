#include"Render2D.h"

Render2D::Render2D(Window* Window) {
	this->CurrentWindow = Window;

	this->VertexArray = new VAO();
	this->VertexBuffer = new VBO();
	this->ElementBuffer = new EBO();


	this->VertexArray->LinkAttrib(*this->VertexBuffer, 0, 2, GL_FLOAT, 8 * sizeof(float), (void*)0);
	this->VertexArray->LinkAttrib(*this->VertexBuffer, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	this->VertexArray->LinkAttrib(*this->VertexBuffer, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void Render2D::DrawPolygon2D(std::vector<Vertex> Vertices, std::vector<GLuint> Indices, float Scale, Vector2Int Position, ShaderProgram* Shaders) {
	//TODO: fix this cause it's not working :(
	this->VertexArray->Bind();
	this->VertexBuffer->Bind();
	this->ElementBuffer->Bind();

	this->VertexBuffer->SetBufferData(Vertices);
	this->ElementBuffer->SetBufferData(Indices);

	this->VertexArray->Unbind();
	this->VertexBuffer->Unbind();
	this->ElementBuffer->Unbind();

	this->VertexArray->Bind();

	glUniform2i(glGetUniformLocation(Shaders->ID, "Position"), Position.X, Position.Y);
	glUniform1i(glGetUniformLocation(Shaders->ID, "Scale"), Scale);

	glBindVertexArray(this->VertexArray->ID);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	this->VertexArray->Unbind();
	this->VertexBuffer->Unbind();
	this->ElementBuffer->Unbind();
}

/* TODO: fix this function, uses now updated functions with different params
void Render2D::DrawSquare(Color RectColor, float Scale, Vector2 Position, ShaderProgram* Shaders) {
	// Vertices coordinates
	GLfloat Vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};

	// Indices for vertices order
	GLuint Indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};

	Render2D::VertexArray->Bind();
	Render2D::VertexBuffer->Bind();
	Render2D::ElementBuffer->Bind();

	Render2D::VertexBuffer->SetBufferData(Vertices, sizeof(Vertices));
	Render2D::ElementBuffer->SetBufferData(Indices, sizeof(Indices));

	Render2D::VertexArray->LinkAttrib(*Render2D::VertexBuffer, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	Render2D::VertexArray->LinkAttrib(*Render2D::VertexBuffer, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	Render2D::VertexArray->LinkAttrib(*Render2D::VertexBuffer, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	Render2D::VertexArray->Unbind();
	Render2D::VertexBuffer->Unbind();
	Render2D::ElementBuffer->Unbind();

	Render2D::VertexArray->Bind();

	glUniform1f(glGetUniformLocation(Shaders->ID, "Scale"), Scale);

	glUniform2f(glGetUniformLocation(Shaders->ID, "Position"), Position.X, Position.Y);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	Render2D::VertexArray->Unbind();
	Render2D::VertexBuffer->Unbind();
	Render2D::ElementBuffer->Unbind();
}
*/