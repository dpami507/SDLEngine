#include <iostream>
#include <algorithm>
#include <random>

#include "Tracked.h"

class Color : public Tracked
{
public:
	Color();
	Color(int red, int green, int blue, int alpha);
	~Color();

	//Getters
	int getRed() { return mRed; }
	int getGreen() { return mGreen; }
	int getBlue() { return mBlue; }
	int getAlpha() { return mAlpha; }

	//Setters
	void setRed(int red);
	void setGreen(int green);
	void setBlue(int blue);
	void setAlpha(int alpha);

	static Color getRandColor();

private:
	uint32_t mRed, mGreen, mBlue, mAlpha;
};