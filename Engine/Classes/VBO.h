#ifndef GL_VBO
#define GL_VBO

#include<glad/glad.h>
#include<vector>

#include"Vector2Int.h"
#include"Vector3.h"
#include"Color.h"

struct Vertex {
	Vector3 VPosition;
	Vector3 VNormal;
	Color VColor;
	Vector2Int UV;
};

class VBO {
	public:
		VBO();

		void SetBufferData(std::vector<Vertex>& Vertices);

		void Bind();
		void Unbind();
		void Destroy();

		GLuint ID;
};

#endif
