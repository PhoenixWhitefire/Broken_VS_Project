#ifndef MESH
#define MESH

#include"Texture.h"
#include"VBO.h"

#include<GLFW/glfw3.h>
#include<vector>

class Mesh {
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

		std::vector<Vertex> Vertices;
		std::vector<GLuint> Indices;
		std::vector<Texture> Textures;
};

#endif
