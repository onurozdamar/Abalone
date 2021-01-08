#pragma once
class Renk
{
public:
	Renk(float red, float green, float blue);
	Renk(int red, int green, int blue);
	float getRed();
	float getGreen();
	float getBlue();
	float getAlpha();
	void setRed(float red);
	void setGreen(float green);
	void setBlue(float blue);
	void setRed(int red);
	void setGreen(int green);
	void setBlue(int blue);
	void setAlpha(float alpha);

private:
	float red, green, blue, alpha;
};

