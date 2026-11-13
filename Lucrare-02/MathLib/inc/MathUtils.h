#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <iostream>
#include <string>

namespace MathUtils {

    struct Vector2D {
        double x;
        double y;

        Vector2D(double xVal = 0.0, double yVal = 0.0);

        double magnitude() const;
        Vector2D normalized() const;
        void print(const std::string& label = "") const;
    };

    // Vector operations
    double dotProduct(const Vector2D& a, const Vector2D& b);
    double distance(const Vector2D& a, const Vector2D& b);
    Vector2D add(const Vector2D& a, const Vector2D& b);

    // Scalar arithmetic and utility functions
    long long factorial(int n);
    int gcd(int a, int b);
    double clamp(double value, double minVal, double maxVal);
    double lerp(double start, double end, double t);

    // Library info
    std::string getLibraryVersion();

} // namespace MathUtils

#endif // MATH_UTILS_H
