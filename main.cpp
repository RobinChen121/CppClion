#include <iostream>
#include <Eigen/Dense>

int main() {
    Eigen::MatrixXd m(2, 2);
    m << 1, 2, 3, 4;
    std::cout << "Matrix:\n" << m << std::endl;
    return 0;
}
