//TODO: find out if you need header files to make classes
//srsly, this is getting ridiculous
//like half of the code files are header files

#ifndef GAME_LOGIC
#define GAME_LOGIC

#include"Display.h"

#include"Camera.h"

#include"Render3D.h"

class Game {
	public:
		Game(Display* Window, Render3D* Renderer3D);

		bool IsKeyPressed(GLenum Key);
		void Update(float Delta);

		Display* MainWindow;
		GLFWwindow* GLWindow;

		Camera* MainCamera;

		bool FirstClick = true;

		Render3D* Renderer3D;
};

#endif
