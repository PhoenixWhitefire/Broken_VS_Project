#include"GameObject.h"

GameObject::GameObject(DefaultShape Shape, bool Is3D) {
	if (Shape == DefaultShape::SHAPE3D_RECT) {
		Color Magenta = Color(1, 1, 1);

		std::vector<Vertex> Vertices;

		Vertices.push_back(Vertex{ Vector3(-0.5f, -0.5f,  0.5f), Vector3(0.0f, 1.0f, 0.0f), Magenta, Vector2Int(1, 0) });
		Vertices.push_back(Vertex{ Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Magenta, Vector2Int(0, 0) });
		Vertices.push_back(Vertex{ Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Magenta, Vector2Int(1, 0) });
		Vertices.push_back(Vertex{ Vector3(0.5f, -0.5f,  0.5f), Vector3(0.0f, 1.0f, 0.0f), Magenta, Vector2Int(0, 0) });

		Vertices.push_back(Vertex{ Vector3(-0.5f,  0.5f,  0.5f), Vector3(0.0f, 1.0f, 0.0f), Magenta, Vector2Int(1, 1) });
		Vertices.push_back(Vertex{ Vector3(-0.5f,  0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Magenta, Vector2Int(0, 1) });
		Vertices.push_back(Vertex{ Vector3(0.5f,  0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Magenta, Vector2Int(1, 1) });
		Vertices.push_back(Vertex{ Vector3(0.5f,  0.5f,  0.5f), Vector3(0.0f, 1.0f, 0.0f), Magenta, Vector2Int(0, 1) });

		std::vector<GLuint> Indices;

		Indices.push_back(0);
		Indices.push_back(1);
		Indices.push_back(2);

		Indices.push_back(0);
		Indices.push_back(2);
		Indices.push_back(3);

		Indices.push_back(0);
		Indices.push_back(4);
		Indices.push_back(7);

		Indices.push_back(0);
		Indices.push_back(7);
		Indices.push_back(3);

		Indices.push_back(3);
		Indices.push_back(7);
		Indices.push_back(6);

		Indices.push_back(3);
		Indices.push_back(6);
		Indices.push_back(2);

		Indices.push_back(2);
		Indices.push_back(6);
		Indices.push_back(5);

		Indices.push_back(2);
		Indices.push_back(5);
		Indices.push_back(1);

		Indices.push_back(1);
		Indices.push_back(5);
		Indices.push_back(4);

		Indices.push_back(1);
		Indices.push_back(4);
		Indices.push_back(0);

		Indices.push_back(4);
		Indices.push_back(6);
		Indices.push_back(5);

		Indices.push_back(4);
		Indices.push_back(6);
		Indices.push_back(7);

		std::vector<Texture> Textures;

		Textures.push_back(Texture("Assets/Textures/MISSING.png", "Diffuse", 0, GL_RGBA));

		this->ObjectMesh = new Mesh(Vertices, Indices, Textures);
	}
	else {
		printf("Unknown shape!\n");

		std::vector<Vertex> Vertices;
		std::vector<GLuint> Indices;
		std::vector<Texture> Textures;

		this->ObjectMesh = new Mesh(Vertices, Indices, Textures);
	}

	this->Is3DObject = Is3D;

	this->Shape = Shape;
}
