#include "Renk.h"

Renk::Renk(float red, float green, float blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = 0;
}

Renk::Renk(int red, int green, int blue) {
	this->red = red % 256 / (float)255;
	this->green = green % 256 / (float)255;
	this->blue = blue % 256 / (float)255;
	this->alpha = 0;
}

void Renk::setRed(float red) {
	this->red = red;
}

void Renk::setGreen(float green) {
	this->green = green;
}

void Renk::setBlue(float blue) {
	this->blue = blue;
}

void Renk::setAlpha(float alpha) {
	this->alpha = alpha;
}

void Renk::setRed(int red) {
	this->red = red % 256 / (float)255;
}

void Renk::setGreen(int green) {
	this->green = green % 256 / (float)255;
}

void Renk::setBlue(int blue) {
	this->blue = blue % 256 / (float)255;
}

float Renk::getRed() {
	return red;
}

float Renk::getGreen() {
	return green;
}

float Renk::getBlue() {
	return blue;
}

float Renk::getAlpha() {
	return alpha;
}
