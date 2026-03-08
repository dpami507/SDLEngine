#pragma once
#include <iostream>
#include <string>

#include "Tracked.h"

class Vector2 : public Tracked
{
public:
    static Vector2 zero() { return Vector2(0, 0); }
    static Vector2 one() { return Vector2(1, 1); }

    static Vector2 up() { return Vector2(0, 1); }
    static Vector2 down() { return Vector2(0, -1); }
    static Vector2 right() { return Vector2(1, 0); }
    static Vector2 left() { return Vector2(-1, 0); }

    Vector2(double x = 0, double y = 0) : x(x), y(y) {}

    //Return normalizied value
    Vector2 normalized();
    //Return magnitude
    double magnitude();

    //Vector Addition
    Vector2 operator+(const Vector2& lVector) const;
    Vector2& operator+=(const Vector2& lVector);

    //Vector Subraction
    Vector2 operator-(const Vector2& lVector) const;
    Vector2& operator-=(const Vector2& lVector);

    //Vector Multiply with Double
    Vector2 operator*(const double& lDouble) const;
    Vector2& operator*=(const double& lDouble);

    //Dot Product
    double Dot(const Vector2& otherVector);
    static double Dot(const Vector2& aVector, const Vector2& bVector);

    //Cout
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);

    //Variables
    double x, y;
};