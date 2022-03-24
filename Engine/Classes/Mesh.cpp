#include"Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) {
	this->Vertices = std::vector<Vertex>();
	this->Indices = std::vector<GLuint>();
	this->Textures = std::vector<Texture>();

	this->Vertices = vertices;
	this->Indices = indices;
	this->Textures = textures;
}
