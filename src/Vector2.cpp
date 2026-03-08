#include "Vector2.h"

//Return normalizied value
Vector2 Vector2::normalized()
{
    if (magnitude() == 0)
        return Vector2(0, 0);

    return Vector2(x / magnitude(), y / magnitude());
}
//Return magnitude
double Vector2::magnitude()
{
    return sqrt((x * x) + (y * y));
}

//Vector Addition
Vector2 Vector2::operator+(const Vector2& lVector) const
{
    return Vector2(x + lVector.x, y + lVector.y);
}
Vector2& Vector2::operator+=(const Vector2& lVector)
{
    x += lVector.x;
    y += lVector.y;
    return *this;
}

//Vector Subraction
Vector2 Vector2::operator-(const Vector2& lVector) const
{
    return Vector2(x - lVector.x, y - lVector.y);
}
Vector2& Vector2::operator-=(const Vector2& lVector)
{
    x -= lVector.x;
    y -= lVector.y;
    return *this;
}

//Multiplication
Vector2 Vector2::operator*(const double& lDouble) const
{
    return Vector2(x * lDouble, y * lDouble);
}
Vector2& Vector2::operator*=(const double& lDouble)
{
    x *= lDouble;
    y *= lDouble;
    return *this;
}

//Dot Product
double Vector2::Dot(const Vector2& otherVector)
{
    return x * otherVector.x + y * otherVector.y;
}
double Vector2::Dot(const Vector2& aVector, const Vector2& bVector)
{
    return aVector.x * bVector.x + aVector.y * bVector.y;
}

//Cout
std::ostream& operator<<(std::ostream& os, const Vector2& vector)
{
    os << "Vector2(" << vector.x << ", " << vector.y << ")";
    return os;
}