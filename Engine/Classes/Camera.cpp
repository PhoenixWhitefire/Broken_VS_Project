//i've effectively robbed this thing of most of it's code by moving those to the main() function and the GameLogic.cpp file... R.I.P

#include"Camera.h"

Camera::Camera(Vector2Int WindowSize) {
	this->Speed = this->CameraSpeed;

	this->WindowWidth = WindowSize.X;
	this->WindowHeight = WindowSize.Y;
}

void Camera::Update() {
	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

	ViewMatrix = glm::lookAt(this->Position, this->Position + this->LookVec, this->UpVec);
	ProjectionMatrix = glm::perspective(glm::radians(this->FOV), (float)this->WindowWidth / this->WindowHeight, this->NearPlane, this->FarPlane);

	this->Matrix = ProjectionMatrix * ViewMatrix;
}
