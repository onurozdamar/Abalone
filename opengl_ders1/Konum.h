#pragma once
#include <iostream>

class Konum
{
public:
	Konum();
	Konum(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	friend std::ostream& operator<<(std::ostream& os, const Konum& obj)
	{
		return os << "o(" << obj.x << ", " << obj.y << ")";
	}
	Konum operator-(const Konum& b) {
		Konum konum;
		konum.x = x - b.x;
		konum.y = y - b.y;
		return konum;
	}
private:
	friend class Cell;
	int x, y;
};

