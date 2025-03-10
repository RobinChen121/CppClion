/*
 * Created by Zhen Chen on 2025/3/9.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */

#include "Var.h"
#include "Model.h"

Var::Var(const int idx, const std::string &n, Model *m)
    : index_(idx), name_(n), model_(m) {
}

// int main() {
//     auto m = Model();
//     const auto x = Var(0, "x", &m);
//     std::cout << "decision variable: " << x.getName() << std::endl;
//
//     return 0;
// }
