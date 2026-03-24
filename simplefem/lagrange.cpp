/// Quadrature rules

#include "lagrange.h"
#include <stdexcept>

using namespace simplefem;

LagrangeElementTriangle::LagrangeElementTriangle(int degree) : _degree(degree) {}

double LagrangeElementTriangle::evaluate(int basis_function_index,
                                         std::vector<double> point) {
  switch(_degree) {
    case 1:
      switch(basis_function_index) {
        case 0:
          return 1.0 - point[0] - point[1];
        case 1:
          return point[0];
        case 2:
          return point[1];
      default:
        throw std::runtime_error("Incorrect basis function index");
      }
    default:
      throw std::runtime_error("Unsupported degree");
  }

  return 0.0;
}
