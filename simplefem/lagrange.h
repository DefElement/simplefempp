/// Lagrange finite elements

#pragma once

#include <vector>

namespace simplefem {

/// A Lagrange element on a triangle
class LagrangeElementTriangle {

public:
  /// Create an element of the given degree
  LagrangeElementTriangle(int degree);

  /// Number of basis functions
  std::size_t dim();

  /// Evaluate a basis function at a single point
  double evaluate(int basis_function_index, std::vector<double> point);

private:
  int _degree;
};

} // namespace simplefem
