#ifndef CLASS_RENDER3D
#define CLASS_RENDER3D

#include"ShaderProgram.h"
#include"Window.h"
#include"VAO.h"
#include"EBO.h"

#include"Vector3.h"
#include"Mesh.h"

#include<vector>

class Render3D {
	public:
		Render3D(Window* Window);

		void Draw(
			Mesh* Object,
			Vector3 Position, Vector3 Size,
			ShaderProgram* Shaders
		);

	private:
		Window* CurrentWindow;

		VAO* VertexArray;
		VBO* VertexBuffer;
		EBO* ElementBuffer;
};

#endif

