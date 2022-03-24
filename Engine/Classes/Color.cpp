#include "Color.h"

//TODO: research function constructors
//I want something like Color.fromRGB instead of relying on function overloads

Color::Color(float R, float G, float B) {
	Color::R = R;
	Color::G = G;
	Color::B = B;
}

Color::Color(int R, int G, int B) {
	Color::R = (float)R / 255;
	Color::G = (float)G / 255;
	Color::B = (float)B / 255;
}

Color::Color() {
	Color::R = 0;
	Color::G = 0;
	Color::B = 0;
}
