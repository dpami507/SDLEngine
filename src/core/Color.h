#pragma once
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
	inline int getRed() const { return mRed; }
	inline int getGreen() const { return mGreen; }
	inline int getBlue() const { return mBlue; }
	inline int getAlpha()const { return mAlpha; }

	//Setters
	void setRed(int red);
	void setGreen(int green);
	void setBlue(int blue);
	void setAlpha(int alpha);

	static Color getRandColor();

private:
	uint32_t mRed, mGreen, mBlue, mAlpha;
};