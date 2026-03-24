/// Polynomials

#pragma once

#include <vector>

namespace simplefem {

/// Tabulate orthonormal polynomials at a point
std::vector<double> tabulate(std::vector<double> point, int degree);

} // namespace simplefem
