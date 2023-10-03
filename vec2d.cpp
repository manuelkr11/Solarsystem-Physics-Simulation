#include "Vec2d.h"

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator=(const Vector2D& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

double Vector2D::norm() const {
    return sqrt((x * x) + (y * y));
}

Vector2D operator*(double scalar, const Vector2D& vector) {
    return vector * scalar;
}
