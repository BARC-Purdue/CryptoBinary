#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

// Function to multiply two matrices
Matrix multiply_matrices(const Matrix &A, const Matrix &B) {
    size_t n = A.size();
    Matrix C(n, Vector(n, 0.0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Function to perform numerical integration using the trapezoidal rule
double trapezoidal_rule(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; ++i) {
        sum += f(a + i * h);
    }

    return sum * h;
}

// Function to solve a system of linear equations using Gaussian elimination
Vector gaussian_elimination(Matrix A, Vector b) {
    size_t n = A.size();

    for (size_t i = 0; i < n; ++i) {
        // Pivoting
        size_t maxRow = i;
        for (size_t k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        std::swap(A[i], A[maxRow]);
        std::swap(b[i], b[maxRow]);

        // Elimination
        for (size_t k = i + 1; k < n; ++k) {
            double c = -A[k][i] / A[i][i];
            for (size_t j = i; j < n; ++j) {
                A[k][j] += c * A[i][j];
            }
            b[k] += c * b[i];
        }
    }

    // Back substitution
    Vector x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i] / A[i][i];
        for (int k = i - 1; k >= 0; --k) {
            b[k] -= A[k][i] * x[i];
        }
    }

    return x;
}

// Example function for numerical integration
double example_function(double x) {
    return std::sin(x);
}

int main() {
    std::srand(std::time(nullptr)); // Seed the random number generator

    // Matrix multiplication
    size_t matrix_size = 500; // Set a large size for heavy computation
    Matrix A(matrix_size, Vector(matrix_size));
    Matrix B(matrix_size, Vector(matrix_size));

    // Fill matrices A and B with random values
    for (size_t i = 0; i < matrix_size; ++i) {
        for (size_t j = 0; j < matrix_size; ++j) {
            A[i][j] = static_cast<double>(rand()) / RAND_MAX;
            B[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    std::cout << "Performing matrix multiplication..." << std::endl;
    Matrix C = multiply_matrices(A, B);
    std::cout << "Matrix multiplication completed." << std::endl;

    // Numerical integration
    double a = 0.0, b = M_PI;
    int n_intervals = 1000000; // Increase for more accuracy and computation
    std::cout << "Performing numerical integration..." << std::endl;
    double integral_result = trapezoidal_rule(example_function, a, b, n_intervals);
    std::cout << "Numerical integration result: " << integral_result << std::endl;

    // Solving a system of linear equations
    Matrix A_linear = {
        {3, 2, -4},
        {2, 3, 3},
        {5, -3, 1}
    };
    Vector b_linear = {3, 15, 14};

    std::cout << "Solving a system of linear equations using Gaussian elimination..." << std::endl;
    Vector solution = gaussian_elimination(A_linear, b_linear);

    std::cout << "Solution to the system of linear equations:" << std::endl;
    for (double x : solution) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

