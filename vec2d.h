#pragma once

#include <cmath>

class Vector2D {
public:
    double x;
    double y;

    Vector2D(double x = 0.0, double y = 0.0);

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(double scalar) const;
    Vector2D operator/(double scalar) const;
    Vector2D& operator+=(const Vector2D&);
    Vector2D& operator-=(const Vector2D&);

    Vector2D& operator=(const Vector2D& other);

    double norm() const;
    void rst();
};

Vector2D operator*(double scalar, const Vector2D& vector);