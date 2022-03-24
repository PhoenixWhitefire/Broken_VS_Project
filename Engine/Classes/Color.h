#ifndef CLASS_COLOR
#define CLASS_COLOR

class Color {
	public:
		float R, G, B;

		/**
		Create a color from a range of 0 to 1
		@param The R, G and B values of the color
		@return A color made from the specified RGB values
		*/
		Color(float R, float G, float B);

		/**
		Create a color from a range of 0 to 255
		@param The R, G and B values of the color
		@return A color made from the specified RGB values
		*/
		Color(int R, int G, int B);

		/**
		Create a blank (black) color
		@return The color black
		*/
		Color();
};

#endif

