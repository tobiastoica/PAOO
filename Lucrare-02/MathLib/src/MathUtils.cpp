#include "MathUtils.h"
#include <cmath>
#include <stdexcept>

namespace MathUtils {

    Vector2D::Vector2D(double xVal, double yVal) : x(xVal), y(yVal) {}

    double Vector2D::magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2D Vector2D::normalized() const {
        double mag = magnitude();
        if (mag == 0.0) {
            return Vector2D(0.0, 0.0);
        }
        return Vector2D(x / mag, y / mag);
    }

    void Vector2D::print(const std::string& label) const {
        if (!label.empty()) {
            std::cout << label << " ";
        }
        std::cout << "(" << x << ", " << y << ")\n";
    }

    double dotProduct(const Vector2D& a, const Vector2D& b) {
        return a.x * b.x + a.y * b.y;
    }

    double distance(const Vector2D& a, const Vector2D& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Vector2D add(const Vector2D& a, const Vector2D& b) {
        return Vector2D(a.x + b.x, a.y + b.y);
    }

    long long factorial(int n) {
        if (n < 0) {
            throw std::invalid_argument("Factorialul nu este definit pentru numere negative!");
        }
        long long result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    int gcd(int a, int b) {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    double clamp(double value, double minVal, double maxVal) {
        if (value < minVal) return minVal;
        if (value > maxVal) return maxVal;
        return value;
    }

    double lerp(double start, double end, double t) {
        return start + t * (end - start);
    }

    std::string getLibraryVersion() {
        return "MathLib v1.0.0 (Static Library - PAOO)";
    }

} // namespace MathUtils
