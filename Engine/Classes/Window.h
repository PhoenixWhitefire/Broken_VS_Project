//For interfacing with GLFWwindow

#ifndef WINDOW
#define	WINDOW

#include"Camera.h"
#include"Vector2.h"
#include"Vector2Int.h"
#include"Color.h"

#include<GLFW/glfw3.h>

class Window {
	public:
		Window(Vector2Int WindowSize, Color BackgroundColor);

		/**
		Destroys the internally used GLFWwindow, terminates GLFW and sets the GLWindow member to NULL, effectively locking any of it's functions
		*/
		~Window();

		void DoPreRender();
		void Render();

		bool IsKeyPressed(GLenum Key);
		bool ShouldClose();

		GLFWwindow* GLWindow;

		Color BkColor;

		Vector2Int Size;
};

#endif

