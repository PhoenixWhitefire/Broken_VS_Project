#ifndef GAMEOBJECT_RENDERABLE3D
#define GAMEOBJECT_RENDERABLE3D

#include<vector>

#include"Color.h"

#include"Texture.h"
#include"Mesh.h"

enum class DefaultShape { SHAPE3D_RECT , SHAPE3D_CUSTOM , SHAPE2D_RECT, SHAPE2D_CUSTOM};

enum class ComponentType { LIGHT };

class Component {
	public:
		ComponentType Type;
};

class GameObject {
	public:
		GameObject(DefaultShape Shape, bool Is3D);

		Mesh* ObjectMesh;

		Vector3 Position = Vector3(0, 0, 0);
		Vector3 Size = Vector3(2, 1, 4);

		Color ObjectColor;

		bool Is3DObject;

		bool Enabled = true;

		DefaultShape Shape;

		std::vector<Component> Components;
};

#endif
