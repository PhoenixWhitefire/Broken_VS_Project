#include"Engine.h"

void SetTextureUniformsForShaders(ShaderProgram* Shaders, Mesh& mesh) {
	Shaders->Activate();

	int NumDiffuse = 0;
	int NumSpecular = 0;

	glUniform1i(glGetUniformLocation(Shaders->ID, "HasDiffuse"), 0);
	glUniform1i(glGetUniformLocation(Shaders->ID, "HasSpecular"), 0);

	for (unsigned int Index = 0; Index < mesh.Textures.size(); Index++) {
		std::string NumberOf;
		std::string Type = mesh.Textures[Index].Type;

		if (Type == "Diffuse") {
			glUniform1i(glGetUniformLocation(Shaders->ID, "HasDiffuse"), 1);

			NumberOf = std::to_string(NumDiffuse++);
		}
		else if (Type == "Specular") {
			glUniform1i(glGetUniformLocation(Shaders->ID, "HasSpecular"), 1);

			NumberOf = std::to_string(NumSpecular++);
		}
		else {
			printf("Unknown texture type, cannot set uniform. Type: %s\n", Type.c_str());

			continue;
		}
		mesh.Textures[Index].TexUnit(Shaders, (Type + NumberOf).c_str(), Index);
		mesh.Textures[Index].Bind();
	}
}

void Engine::OnWindowResize(GLFWwindow* GLWindow, int Width, int Height) {
	//glViewport(0, 0, Width, Height);

	//this->MainCamera->WindowWidth = Width;
	//this->MainCamera->WindowHeight = Height;

	//this->MainWindow->Size = Vector2Int(Width, Height);
}

Engine::Engine(Vector2Int WindowStartSize, std::string WorkingDirectory) {
	this->CurrentDirectory = WorkingDirectory.append("/Engine");

	this->MainWindow = new Window(WindowStartSize, Color(0.529f, 0.808f, 0.922f));
	this->MainCamera = new Camera(WindowStartSize);

	this->Shaders3D = new ShaderProgram(this->CurrentDirectory + "/Shaders/base3d.vert", this->CurrentDirectory + "/Shaders/base3d.frag");
	this->Shaders2D = new ShaderProgram(this->CurrentDirectory + "/Shaders/base2d.vert", this->CurrentDirectory + "/Shaders/base2d.frag");

	this->Renderer3D = new Render3D(this->MainWindow);
	this->Renderer2D = new Render2D(this->MainWindow);

	glEnable(GL_DEPTH_TEST);

	this->Shaders3D->Activate();

	glUniform1i(glGetUniformLocation(this->Shaders3D->ID, "UseTexture"), 0);

	//glfwSetWindowUserPointer(this->MainWindow->GLWindow, this);

	//auto ResizeWindow = [](GLFWwindow* GLWindow, int Width, int Height) {
		//static_cast<Engine*>(glfwGetWindowUserPointer(GLWindow))->OnWindowResize(GLWindow, Width, Height);
	//};

	//glfwSetWindowSizeCallback(this->MainWindow->GLWindow, ResizeWindow);

	Debug::Log("Engine init");
}

void Engine::Start(std::function<void(Engine*, double, double)> FrameStartCallback, std::function<void(Engine*, double, double)> FrameEndCallback) {
	double LastTime = glfwGetTime();

	this->Shaders3D->Activate();

	glUniform3f(glGetUniformLocation(this->Shaders3D->ID, "LightColor"), 1.0f, 1.0f, 1.0f);

	glUniform3f(
		glGetUniformLocation(this->Shaders3D->ID, "LightPosition"),
		5.0f,
		0.0f,
		5.0f
	);

	while (!this->MainWindow->ShouldClose() || this->Exit) {
		this->MainCamera->Update();

		this->MainWindow->DoPreRender();

		double CurrentTime = glfwGetTime();

		double DeltaTime = CurrentTime - LastTime;

		LastTime = CurrentTime;

		double FrameStart = glfwGetTime();

		if (FrameStartCallback) {
			FrameStartCallback(this, CurrentTime, DeltaTime);
		}

		glUniformMatrix4fv(glGetUniformLocation(this->Shaders3D->ID, "CameraMatrix"), 1, GL_FALSE, glm::value_ptr(this->MainCamera->Matrix));
		glUniform3f(glGetUniformLocation(Shaders3D->ID, "CameraPosition"), this->MainCamera->Position.x, this->MainCamera->Position.y, this->MainCamera->Position.z);

		glUniform1f(glGetUniformLocation(Shaders3D->ID, "Time"), (float)glfwGetTime());
		glUniform1f(glGetUniformLocation(Shaders2D->ID, "Time"), (float)glfwGetTime());

		for (int Index = 0; Index < this->GameObjects.size(); Index++) {
			GameObject* Object = this->GameObjects[Index];

			if (Object->Enabled) {
				if (Object->Components.size() > 0 && Object->Components[0].Type == ComponentType::LIGHT) {
					this->Shaders3D->Activate();

					//glUniform3f(glGetUniformLocation(this->Shaders3D->ID, "LightPosition"), Object->Position.X, Object->Position.Y, Object->Position.Z);
				}

				if (Object->Is3DObject) {
					if (Object->ObjectMesh != nullptr) {
						SetTextureUniformsForShaders(this->Shaders3D, *Object->ObjectMesh);
					}

					this->Renderer3D->Draw(Object->ObjectMesh, Object->Position, Object->Size, this->Shaders3D);
				}
				else {
					if (Object->Shape == DefaultShape::SHAPE2D_RECT) {
						printf("fix here Engine.cpp 137: Object-> == DefaultShape::SHAPE2D_RECT\n");
						//TODO: fix plox
						//this->Renderer2D->DrawSquare(Color(0, 1, 0), Object->Size.X, Vector2(Object->Position.X, Object->Position.Y), this->Shaders2D);
					}
				}
			}
		}

		if (FrameEndCallback) {
			FrameEndCallback(this, FrameStart, glfwGetTime() - FrameStart);
		}

		this->MainWindow->Render();
	}
}

bool Engine::IsKeyPressed(GLenum Key) {
	return this->MainWindow->IsKeyPressed(Key);
}

Engine::~Engine() {
	this->Exit = true;

	Debug::Log("Engine closing...");

	this->MainWindow->~Window();
	this->Shaders3D->~ShaderProgram();
	this->Shaders2D->~ShaderProgram();
}
