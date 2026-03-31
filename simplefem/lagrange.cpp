/// Quadrature rules

#include "lagrange.h"
#include <stdexcept>

using namespace simplefem;

LagrangeElementTriangle::LagrangeElementTriangle(int degree)
    : _degree(degree) {}

double LagrangeElementTriangle::evaluate(int basis_function_index,
                                         std::vector<double> point) {
  switch (_degree) {
  case 1:
    switch (basis_function_index) {
    case 0:
      return 1.0 - point[0] - point[1];
    case 1:
      return point[0];
    case 2:
      return point[1];
    default:
      throw std::runtime_error("Incorrect basis function index");
    }
  case 2:
    switch (basis_function_index) {
    case 0:
      return (1.0 - point[0] - point[1]) * (1.0 - 2 * point[0] - 2 * point[1]);
    case 1:
      return (1.0 - point[0] - point[1]) * 4 * point[0];
    case 2:
      return point[0] * (2 * point[0] - 1);
    case 3:
      return (1.0 - point[0] - point[1]) * 4 * point[1];
    case 4:
      return 4 * point[0] * point[1];
    case 5:
      return point[1] * (2 * point[1] - 1);
    default:
      throw std::runtime_error("Incorrect basis function index");
    }
  case 3:
    switch (basis_function_index) {
    case 0:
      return -9 * point[0] * point[0] * point[0] / 2 -
             27 * point[0] * point[0] * point[1] / 2 + 9 * point[0] * point[0] -
             27 * point[0] * point[1] * point[1] / 2 +
             18 * point[0] * point[1] - 11 * point[0] / 2 -
             9 * point[1] * point[1] * point[1] / 2 + 9 * point[1] * point[1] -
             11 * point[1] / 2 + 1;
    case 1:
      return 27 * point[0] * point[0] * point[0] / 2 +
             27 * point[0] * point[0] * point[1] -
             45 * point[0] * point[0] / 2 +
             27 * point[0] * point[1] * point[1] / 2 -
             45 * point[0] * point[1] / 2 + 9 * point[0];
    case 2:
      return -27 * point[0] * point[0] * point[0] / 2 -
             27 * point[0] * point[0] * point[1] / 2 +
             18 * point[0] * point[0] + 9 * point[0] * point[1] / 2 -
             9 * point[0] / 2;
    case 3:
      return 9 * point[0] * point[0] * point[0] / 2 -
             9 * point[0] * point[0] / 2 + point[0];
    case 4:
      return 27 * point[0] * point[0] * point[1] / 2 +
             27 * point[0] * point[1] * point[1] -
             45 * point[0] * point[1] / 2 +
             27 * point[1] * point[1] * point[1] / 2 -
             45 * point[1] * point[1] / 2 + 9 * point[1];
    case 5:
      return -27 * point[0] * point[0] * point[1] -
             27 * point[0] * point[1] * point[1] + 27 * point[0] * point[1];
    case 6:
      return 27 * point[0] * point[0] * point[1] / 2 -
             9 * point[0] * point[1] / 2;
    case 7:
      return -27 * point[0] * point[1] * point[1] / 2 +
             9 * point[0] * point[1] / 2 -
             27 * point[1] * point[1] * point[1] / 2 +
             18 * point[1] * point[1] - 9 * point[1] / 2;
    case 8:
      return 27 * point[0] * point[1] * point[1] / 2 -
             9 * point[0] * point[1] / 2;
    case 9:
      return 9 * point[1] * point[1] * point[1] / 2 -
             9 * point[1] * point[1] / 2 + point[1];
    default:
      throw std::runtime_error("Incorrect basis function index");
    }
  default:
    throw std::runtime_error("Unsupported degree");
  }

  return 0.0;
}

std::size_t LagrangeElementTriangle::dim() {
  return (_degree + 1) * (_degree + 2) / 2;
}

