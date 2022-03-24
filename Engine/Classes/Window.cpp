#include"Window.h"

//TODO: research if 'this->MEMBER' is better than 'Display.MEMBER'

void error_callback(int error, const char* description) {
	printf("GLFW error: %s\n", description);
}

Window::Window(Vector2Int WindowSize, Color BackgroundColor) {
	glfwInit();

	this->BkColor = BackgroundColor;
	this->Size = WindowSize;

	//Configure GLFW so it knows what OpenGL version be have (3.3 Core)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback(error_callback);

	this->GLWindow = glfwCreateWindow(this->Size.X, this->Size.Y, "GameTest", NULL, NULL);

	if (this->GLWindow == NULL) {
		printf("Failed to create window!\n");

		glfwTerminate();

		Debug::ShowPrompt("Engine error", "An internal error occured with OpenGL/GLFW. The program will close as it cannot create the main window.", MB_OK, false);

		Debug::Close();

		throw("Failed to create GLFW window!");
	}

	glfwMakeContextCurrent(this->GLWindow);

	gladLoadGL();

	glfwSwapInterval(1); //VSync
	//IMPORTANT / NOTE: DO NOT move glfwSwapInterval above glfwMakeContextCurrent, VSync WILL NOT be applied if you do so, resulting in sky-high CPU usage

	glClearColor(this->BkColor.R, this->BkColor.G, this->BkColor.B, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(GLWindow);

	glViewport(0, 0, this->Size.X, this->Size.Y);
}

bool Window::ShouldClose() {
	if (this->GLWindow == NULL) {
		//Meant to stop you from calling any of the Window classes functions after you've called it's destructor
		printf("glw does no exist\n");
		throw("GLWindow does not exist!");
	}
	else {
		return glfwWindowShouldClose(this->GLWindow);
	}
}

void Window::DoPreRender() {
	if (this->GLWindow == NULL) {
		//Meant to stop you from calling any of the Window classes functions after you've called it's destructor
		printf("no exist glw\n");
		throw("GLWindow does not exist!");
	}

	glClearColor(this->BkColor.R, this->BkColor.G, this->BkColor.B, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //TODO: is GL_COLOR_BUFFER_BIT really necessary to clear? afaik, as long as you have a skybox it won't cause a problem
}

void Window::Render() {
	if (this->GLWindow == NULL) {
		//Meant to stop you from calling any of the Window classes functions after you've called it's destructor
		printf("glw no exit\n");
		throw("GLWindow does not exist!");
	}
	else {
		printf("swapb\n");
		//glfwSwapBuffers(this->GLWindow);

		printf("polle\n");
		glfwPollEvents();

		printf("frame done\n");
	}
}

bool Window::IsKeyPressed(GLenum Key) {
	if (this->GLWindow == NULL) {
		printf("ohnoes1\n");
	}

	return glfwGetKey(this->GLWindow, Key) == GLFW_PRESS;
}

Window::~Window() {
	if (this->GLWindow == NULL) {
		printf("ohnoes2\n");
	}

	glfwDestroyWindow(this->GLWindow);
	glfwTerminate();

	this->GLWindow = NULL;
}

