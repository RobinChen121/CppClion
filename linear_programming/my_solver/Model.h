/*
 * Created by Zhen Chen on 2025/3/9.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <vector>

class Var;

class Model {
private:
    std::vector<double> obj_coeffs_;
    std::vector<double> var_lb_;
    std::vector<double> var_ub_;
    std::vector<std::string> var_names_;
    std::vector<double> row_lb_;
    std::vector<double> row_ub_;
    bool is_minimization_;

public:
    Model() : is_minimization_(true) {
    }

    Var addVar(double lb, double ub, double obj_coeff);

    static void print();
};


#endif //MODEL_H
