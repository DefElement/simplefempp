#include <simplefem/lagrange.h>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace simplefem;

int main() {
    auto e = LagrangeElementTriangle(1);

    std::cout << e.evaluate(0, {0.2, 0.3}) << std::endl;
    std::cout << e.evaluate(1, {0.2, 0.3}) << std::endl;
    std::cout << e.evaluate(2, {0.2, 0.3}) << std::endl;
    assert(std::abs(e.evaluate(0, {0.2, 0.3}) - 0.5) < 1e-7);
    assert(std::abs(e.evaluate(1, {0.2, 0.3}) - 0.2) < 1e-7);
    assert(std::abs(e.evaluate(2, {0.2, 0.3}) - 0.3) < 1e-7);
}
