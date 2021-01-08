#include "Konum.h"

Konum::Konum() {
	this->x = 0;
	this->y = 0;
}

Konum::Konum(int x, int y) {
	this->x = x;
	this->y = y;
}

void Konum::setX(int x) {
	this->x = x;
}

void Konum::setY(int y) {
	this->y = y;
}

int Konum::getX() {
	return x;
}

int Konum::getY() {
	return y;
}