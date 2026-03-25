#include <simplefem/lagrange.h>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace simplefem;

void assert_value(LagrangeElementTriangle& e, int f_index, std::vector<double> point, double value) {
    std::cout << "Basis function " << f_index << ": "
        << e.evaluate(f_index, point)
        << " =?= " << value
        << std::endl;
    assert(std::abs(e.evaluate(f_index, point) - value) < 1e-7);
}

int main() {
    std::cout << "Degree 1" << std::endl;
    auto e1 = LagrangeElementTriangle(1);
    assert_value(e1, 0, {0.2, 0.3}, 0.5);
    assert_value(e1, 1, {0.2, 0.3}, 0.2);
    assert_value(e1, 2, {0.2, 0.3}, 0.3);
    std::cout << std::endl;

    std::cout << "Degree 2" << std::endl;
    auto e2 = LagrangeElementTriangle(2);
    assert_value(e2, 0, {0.2, 0.3}, 0.0);
    assert_value(e2, 1, {0.2, 0.3}, 0.4);
    assert_value(e2, 2, {0.2, 0.3}, -0.12);
    assert_value(e2, 3, {0.2, 0.3}, 0.6);
    assert_value(e2, 4, {0.2, 0.3}, 0.24);
    assert_value(e2, 5, {0.2, 0.3}, -0.12);
    std::cout << std::endl;
}
