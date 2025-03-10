/*
 * Created by Zhen Chen on 2025/3/9.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */

#include "Model.h"
#include "Var.h"


// 添加变量
Var Model::addVar(const double lb, const double ub, const double obj_coeff) {
    const int index = var_names_.size();
    var_lb_.push_back(lb);
    var_ub_.push_back(ub);
    obj_coeffs_.push_back(obj_coeff);
    std::string name = "chen";
    var_names_.push_back(name.empty() ? "x" + std::to_string(index) : name);
    return Var(index, var_names_.back(), this);
}

void Model::print() {
    std::cout << "this is a test." << std::endl;
}

int main() {
    auto m = Model();
    const auto x = Var(0, "x", &m);
    std::cout << "decision variable: " << x.getName() << std::endl;

    // m.addVar(0, 1.0, 1.0, "x");
    m.print();

    return 0;
}
