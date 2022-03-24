#ifndef PHOENIX_ENGINE
#define PHOENIX_ENGINE

#include<filesystem>
#include<functional>
#include<string>
#include<vector>

#include"Classes/Vector2Int.h"
#include"Classes/Window.h"

#include"Classes/Render3D.h"
#include"Classes/Render2D.h"

#include"Classes/GameObject.h"

class Engine {
	public:
		/*
		Creates an Engine object
		@param The size of the window (in integer form with Vector2Int)
		@return An engine object
		*/
		Engine(Vector2Int WindowStartSize, std::string WorkingDirectory);

		/*
		Terminates the current engine thread, and calls destructors on internally-used engine objects
		*/
		~Engine();

		/*
		Starts the execution of the main engine thread
		*/

		/*
		Initializes main engine loop
		Engine* function parameter is to allow code to use engine functions

		@param (Optional) Function to run at start of frame - Params<Engine*>,<double>,<double>: Current tick, Time since last frame
		@param (Optional) Function to run at end of frame - Params<Engine*>,<double>,<double>: Frame start tick, Time taken for frame
		*/

		void Start(std::function<void(Engine*, double, double)> FrameStartCallback, std::function<void(Engine*, double, double) > FrameEndCallback);

		void OnWindowResize(GLFWwindow* GLWindow, int Width, int Height);
		bool IsKeyPressed(GLenum Key);

		ShaderProgram* Shaders3D;
		ShaderProgram* Shaders2D;

		Render3D* Renderer3D;
		Render2D* Renderer2D;

		std::string CurrentDirectory = "";

		//The main scene camera
		Camera* MainCamera;
		//The main engine window
		Window* MainWindow;

		std::vector<GameObject*> GameObjects;

		bool Exit = false;
};

#endif
