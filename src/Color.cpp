#include "Color.h"

Color::Color()
{
	setRed(255);
	setGreen(255);
	setBlue(255);
	setAlpha(255);
}
Color::Color(int red, int green, int blue, int alpha)
{
	setRed(red);
	setGreen(green);
	setBlue(blue);
	setAlpha(alpha);
}
Color::~Color()
{
}

//return a random color
Color Color::getRandColor()
{
	//Create random numbers
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);

	//Set new color to random
	Color color(dis(gen), dis(gen), dis(gen), 255);
	return color;
}

//Set red (0-255)
void Color::setRed(int red)
{
	mRed = std::min(std::max(0, red), 255);
}
//Set green (0-255)
void Color::setGreen(int green)
{
	mGreen = std::min(std::max(0, green), 255);
}
//Set blue (0-255)
void Color::setBlue(int blue)
{
	mBlue = std::min(std::max(0, blue), 255);
}
//Set alpha (0-255)
void Color::setAlpha(int alpha)
{
	mAlpha = std::min(std::max(0, alpha), 255);
}