#include"Engine/Engine.h"

Camera* Player;

bool FirstClick = false;

GLfloat Vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint Indices[] =
{
	0, 1, 2,
	0, 2, 3
};

void HandleInputs(Engine* EObject, double Current, double Delta) {
	EObject->Shaders3D->Activate();

	float Speed = EObject->MainCamera->Speed * Delta;

	if (EObject->IsKeyPressed(GLFW_KEY_W)) {
		EObject->MainCamera->Position += EObject->MainCamera->LookVec * Speed;
	}

	if (EObject->IsKeyPressed(GLFW_KEY_A)) {
		EObject->MainCamera->Position += -glm::normalize(glm::cross(EObject->MainCamera->LookVec, EObject->MainCamera->UpVec)) * Speed;
	}

	if (EObject->IsKeyPressed(GLFW_KEY_S)) {
		EObject->MainCamera->Position += -EObject->MainCamera->LookVec * Speed;
	}

	if (EObject->IsKeyPressed(GLFW_KEY_D)) {
		EObject->MainCamera->Position += glm::normalize(glm::cross(EObject->MainCamera->LookVec, EObject->MainCamera->UpVec)) * Speed;
	}

	if (EObject->IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
		EObject->MainCamera->Speed = EObject->MainCamera->CameraSpeed / 5;
	}
	else {
		EObject->MainCamera->Speed = EObject->MainCamera->CameraSpeed;
	}

	if (glfwGetMouseButton(EObject->MainWindow->GLWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(EObject->MainWindow->GLWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (FirstClick) {
			glfwSetCursorPos(EObject->MainWindow->GLWindow, (EObject->MainCamera->WindowWidth / 2), (EObject->MainCamera->WindowHeight / 2));
			FirstClick = false;
		}

		double MouseX;
		double MouseY;

		glfwGetCursorPos(EObject->MainWindow->GLWindow, &MouseX, &MouseY);

		float RotationX = EObject->MainCamera->MouseSensitivity * (MouseY - (EObject->MainCamera->WindowHeight / 2.0f)) / EObject->MainCamera->WindowHeight;
		float RotationY = EObject->MainCamera->MouseSensitivity * (MouseX - (EObject->MainCamera->WindowWidth / 2.0f)) / EObject->MainCamera->WindowWidth;

		glm::vec3 NewOrientation = glm::rotate(
			EObject->MainCamera->LookVec,
			glm::radians(-RotationX),
			glm::normalize(glm::cross(EObject->MainCamera->LookVec, EObject->MainCamera->UpVec))
		);

		if (abs(glm::angle(NewOrientation, EObject->MainCamera->UpVec) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
			EObject->MainCamera->LookVec = NewOrientation;
		}

		EObject->MainCamera->LookVec = glm::rotate(EObject->MainCamera->LookVec, glm::radians(-RotationY), EObject->MainCamera->UpVec);

		glfwSetCursorPos(EObject->MainWindow->GLWindow, (EObject->MainCamera->WindowWidth / 2), (EObject->MainCamera->WindowHeight / 2));
	}
	else if (glfwGetMouseButton(EObject->MainWindow->GLWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(EObject->MainWindow->GLWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		FirstClick = true;
	}

	//EObject->GameObjects[0]->Position = Vector3(sin(glfwGetTime()) * 20, 5, cos(glfwGetTime()) * 20);
}

int main() {
	Engine Main = Engine(Vector2Int(800, 800), std::filesystem::current_path().string());

	GameObject* Cube = new GameObject(DefaultShape::SHAPE3D_RECT, true);

	Component Light;
	Light.Type = ComponentType::LIGHT;

	Cube->Components.push_back(Light);

	Cube->Position = Vector3(-20, 10, -20);
	Cube->Size = Vector3(2, 2, 2);

	Cube->ObjectColor = Color(1.0f, 1.0f, 1.0f);

	//Main.GameObjects.push_back(Cube);

	GameObject* Plane = new GameObject(DefaultShape::SHAPE3D_RECT, true);
	
	Plane->ObjectMesh->Textures.push_back(Texture("Assets/Textures/planks.png", "Diffuse", 0, GL_RGBA));
	Plane->ObjectMesh->Textures.push_back(Texture("Assets/Textures/planksSpec.png", "Specular", 0, GL_RED));

	Plane->ObjectColor = Color(1.0f, 0.0f, 0.0f);
	
	Main.GameObjects.push_back(Plane);

	Player = Main.MainCamera;
	
	Main.Start(HandleInputs, NULL);

	Main.~Engine();

	Debug::Close();

	return 0;
}
