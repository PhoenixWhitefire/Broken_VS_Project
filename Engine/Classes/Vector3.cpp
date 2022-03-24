#include"Vector3.h"

Vector3::Vector3(double X, double Y, double Z) {
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

Vector3::Vector3() {
	this->X = 0.0f;
	this->Y = 0.0f;
	this->Z = 0.0f;
}
