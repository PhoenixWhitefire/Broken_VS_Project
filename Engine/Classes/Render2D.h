#ifndef CLASS_RENDER2D
#define CLASS_RENDER2D

#include"ShaderProgram.h"
#include"Window.h"
#include"VAO.h"
#include"EBO.h"

#include<iostream>

#include<GLFW/glfw3.h>

class Render2D {
	public:
		Render2D(Window* Window);
		
		void DrawPolygon2D(std::vector<Vertex> Vertices, std::vector<GLuint> Indices, float Scale, Vector2Int Position, ShaderProgram* Shaders);

		//void DrawSquare(Color RectColor, float Scale, Vector2Int Position, ShaderProgram* Shaders);

	private:
		Window* CurrentWindow;

		VAO* VertexArray;
		VBO* VertexBuffer;
		EBO* ElementBuffer;
};

#endif

