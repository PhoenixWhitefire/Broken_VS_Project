//TODO: find out if you need header files to make classes
//srsly, this is getting ridiculous
//like half of the code files are header files

//Handle game-related logic here
//DO NOT put engine-related code here. Handle stuff like controlling the camera in this file instead.

#include"GameLogic.h"

Game::Game(Display* Window, Render3D* Renderer3D) {
	this->MainCamera = new Camera(800, 800);

	this->MainWindow = Window;

	this->GLWindow = this->MainWindow->GLWindow;

	this->Renderer3D = Renderer3D;
}

bool Game::IsKeyPressed(GLenum Key) {
	return glfwGetKey(this->GLWindow, Key) == GLFW_PRESS;
}

void Game::Update(float Delta) {
	float Speed = this->MainCamera->Speed * Delta;

	if (IsKeyPressed(GLFW_KEY_W)) {
		this->MainCamera->Position += this->MainCamera->LookVec * Speed;
	}

	if (IsKeyPressed(GLFW_KEY_A)) {
		this->MainCamera->Position += -glm::normalize(glm::cross(this->MainCamera->LookVec, this->MainCamera->UpVec)) * Speed;
	}

	if (IsKeyPressed(GLFW_KEY_S)) {
		this->MainCamera->Position += -this->MainCamera->LookVec * Speed;
	}

	if (IsKeyPressed(GLFW_KEY_D)) {
		this->MainCamera->Position += glm::normalize(glm::cross(this->MainCamera->LookVec, this->MainCamera->UpVec)) * Speed;
	}

	if (IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
		this->MainCamera->Speed = this->MainCamera->CameraSpeed / 5;
	}
	else {
		this->MainCamera->Speed = this->MainCamera->CameraSpeed;
	}

	if (glfwGetMouseButton(this->GLWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(this->GLWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (this->FirstClick) {
			glfwSetCursorPos(this->GLWindow, (this->MainCamera->WindowWidth / 2), (this->MainCamera->WindowHeight / 2));
			this->FirstClick = false;
		}

		double MouseX;
		double MouseY;

		glfwGetCursorPos(this->GLWindow, &MouseX, &MouseY);

		float RotationX = this->MainCamera->MouseSensitivity * (MouseY - (this->MainCamera->WindowHeight / 2.0f)) / this->MainCamera->WindowHeight;
		float RotationY = this->MainCamera->MouseSensitivity * (MouseX - (this->MainCamera->WindowWidth / 2.0f)) / this->MainCamera->WindowWidth;

		glm::vec3 NewOrientation = glm::rotate(
			this->MainCamera->LookVec,
			glm::radians(-RotationX),
			glm::normalize(glm::cross(this->MainCamera->LookVec, this->MainCamera->UpVec))
		);

		if (abs(glm::angle(NewOrientation, this->MainCamera->UpVec) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
			this->MainCamera->LookVec = NewOrientation;
		}

		this->MainCamera->LookVec = glm::rotate(this->MainCamera->LookVec, glm::radians(-RotationY), this->MainCamera->UpVec);

		glfwSetCursorPos(this->GLWindow, (this->MainCamera->WindowWidth / 2), (this->MainCamera->WindowHeight / 2));
	}
	else if (glfwGetMouseButton(this->GLWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(this->GLWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		FirstClick = true;
	}

	this->MainCamera->Update();
}
