#pragma once
#include <cmath>

struct vec2d
{
    double x;
    double y;

    // Constructor
    vec2d(double x0 = 0.0, double y0 = 0.0)
        : x{x0}, y{y0}
    {
    }

    // Addition
    vec2d operator+(const vec2d& b) const
    {
        return {x + b.x, y + b.y};
    }

    vec2d operator+(double b) const
    {
        return {x + b, y + b};
    }

    // Subtraction
    vec2d operator-(const vec2d& b) const
    {
        return {x - b.x, y - b.y};
    }

    vec2d operator-(double b) const
    {
        return {x - b, y - b};
    }

    // Multiplication (component-wise)
    vec2d operator*(const vec2d& b) const
    {
        return {x * b.x, y * b.y};
    }

    vec2d operator*(double b) const
    {
        return {x * b, y * b};
    }

    // Division (component-wise)
    vec2d operator/(const vec2d& b) const
    {
        return {x / b.x, y / b.y};
    }

    vec2d operator/(double b) const
    {
        return {x / b, y / b};
    }

    // Unary minus
    vec2d operator-() const
    {
        return {-x, -y};
    }

    // Compound assignment
    vec2d& operator+=(const vec2d& b)
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    vec2d& operator-=(const vec2d& b)
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    vec2d& operator*=(double b)
    {
        x *= b;
        y *= b;
        return *this;
    }

    vec2d& operator/=(double b)
    {
        x /= b;
        y /= b;
        return *this;
    }

    // Vector operations
    double dot(const vec2d& b) const
    {
        return x * b.x + y * b.y;
    }

    double squaredLength() const
    {
        return x * x + y * y;
    }

    double norm() const
    {
        return std::sqrt(squaredLength());
    }

    // Scalar on the left
    friend vec2d operator+(double a, const vec2d& b)
    {
        return b + a;
    }

    friend vec2d operator-(double a, const vec2d& b)
    {
        return {a - b.x, a - b.y};
    }

    friend vec2d operator*(double a, const vec2d& b)
    {
        return b * a;
    }

    friend vec2d operator/(double a, const vec2d& b)
    {
        return {a / b.x, a / b.y};
    }

    double cross(const vec2d& b) const
    {
    return x * b.y - y * b.x;
    }

};