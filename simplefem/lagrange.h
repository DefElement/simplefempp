/// Lagrange finite elements

#pragma once

#include <vector>

namespace simplefem {

/// A Lagrange element on a triangle
class LagrangeElementTriangle {

public:
    /// Create an element of the given degree
    LagrangeElementTriangle(int degree);

    /// Evaluate a basis function at a single point
    double evaluate(int basis_function_index, std::vector<double> point);

private:
    int _degree;
    std::vector<std::vector<double>> _coeffs;
};

} // namespace simplefem
