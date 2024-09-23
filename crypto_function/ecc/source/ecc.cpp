#include <iostream>
#include <vector>
#include <tuple>

// Define the Elliptic Curve
struct EllipticCurve {
    long long a, b, p; // Curve parameters: y^2 = x^3 + ax + b over F_p
    EllipticCurve(long long a, long long b, long long p) : a(a), b(b), p(p) {}
};

// Define a point on the curve
struct Point {
    long long x, y;
    bool at_infinity;

    Point() : x(0), y(0), at_infinity(true) {}
    Point(long long x, long long y) : x(x), y(y), at_infinity(false) {}
};

// Function to perform modular inverse
long long modInverse(long long a, long long p) {
    long long m0 = p, t, q;
    long long x0 = 0, x1 = 1;

    if (p == 1) return 0;

    while (a > 1) {
        q = a / p;
        t = p;

        // p is the remainder now, process same as Euclid's algorithm
        p = a % p;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}

// Function to add two points on the curve
Point pointAdd(const EllipticCurve &curve, const Point &P, const Point &Q) {
    if (P.at_infinity) return Q;
    if (Q.at_infinity) return P;

    if (P.x == Q.x && (P.y != Q.y || P.y == 0)) {
        return Point(); // Result is the point at infinity
    }

    long long m;
    if (P.x == Q.x && P.y == Q.y) {
        m = (3 * P.x * P.x + curve.a) * modInverse(2 * P.y, curve.p) % curve.p;
    } else {
        m = (Q.y - P.y) * modInverse(Q.x - P.x, curve.p) % curve.p;
    }

    long long xr = (m * m - P.x - Q.x) % curve.p;
    long long yr = (m * (P.x - xr) - P.y) % curve.p;

    return Point((xr + curve.p) % curve.p, (yr + curve.p) % curve.p);
}

// Function to perform scalar multiplication (n * P)
Point pointMultiply(const EllipticCurve &curve, const Point &P, long long n) {
    Point result;
    Point Q = P;

    while (n > 0) {
        if (n % 2 == 1) {
            result = pointAdd(curve, result, Q);
        }
        Q = pointAdd(curve, Q, Q);
        n = n / 2;
    }

    return result;
}

int main() {
    // Example curve: y^2 = x^3 + 2x + 3 over F_97
    EllipticCurve curve(2, 3, 97);

    // Base point on the curve (for simplicity, using small values)
    Point G(3, 6);

    // Private key (scalar)
    long long privateKey = 15;

    // Public key (publicKey = privateKey * G)
    Point publicKey = pointMultiply(curve, G, privateKey);

    std::cout << "Public Key: (" << publicKey.x << ", " << publicKey.y << ")" << std::endl;

    return 0;
}
