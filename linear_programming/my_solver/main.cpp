/*
 * Created by Zhen Chen on 2025/3/9.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <ClpSimplex.hpp>
#include <CoinPackedMatrix.hpp>

// 前向声明
class Model;

// 表示变量的类
class Var {
private:
    int index_;
    std::string name_;
    Model* model_;

public:
    Var(int idx, const std::string& n, Model* m) : index_(idx), name_(n), model_(m) {}
    int getIndex() const { return index_; }
    std::string getName() const { return name_; }
};

// 线性表达式类
class LinearExpr {
private:
    std::vector<int> indices_;
    std::vector<double> coeffs_;

public:
    LinearExpr() = default;

    // 添加变量项
    LinearExpr& operator+=(const Var& v) {
        indices_.push_back(v.getIndex());
        coeffs_.push_back(1.0);
        return *this;
    }

    LinearExpr& operator-=(const Var& v) {
        indices_.push_back(v.getIndex());
        coeffs_.push_back(-1.0);
        return *this;
    }

    // 系数乘法
    friend LinearExpr operator*(double coeff, const Var& v) {
        LinearExpr expr;
        expr.indices_.push_back(v.getIndex());
        expr.coeffs_.push_back(coeff);
        return expr;
    }

    LinearExpr& operator+=(const LinearExpr& other) {
        for (size_t i = 0; i < other.indices_.size(); ++i) {
            indices_.push_back(other.indices_[i]);
            coeffs_.push_back(other.coeffs_[i]);
        }
        return *this;
    }

    std::vector<int> getIndices() const { return indices_; }
    std::vector<double> getCoeffs() const { return coeffs_; }
};

// 约束类
class Constraint {
private:
    LinearExpr expr_;
    double lb_;
    double ub_;

public:
    Constraint(const LinearExpr& expr, double lb, double ub) : expr_(expr), lb_(lb), ub_(ub) {}

    LinearExpr getExpr() const { return expr_; }
    double getLowerBound() const { return lb_; }
    double getUpperBound() const { return ub_; }
};

// Model 类
class Model {
private:
    ClpSimplex solver_;
    std::vector<double> obj_coeffs_;
    std::vector<double> var_lb_;
    std::vector<double> var_ub_;
    std::vector<std::string> var_names_;
    CoinPackedMatrix constraint_matrix_;
    std::vector<double> row_lb_;
    std::vector<double> row_ub_;
    bool is_maximization_;

public:
    Model() : is_maximization_(true) {
        constraint_matrix_.setDimensions(0, 0);
    }

    // 添加变量
    Var addVar(double lb, double ub, double obj_coeff, const std::string& name = "") {
        int index = var_names_.size();
        var_lb_.push_back(lb);
        var_ub_.push_back(ub);
        obj_coeffs_.push_back(obj_coeff);
        var_names_.push_back(name.empty() ? "x" + std::to_string(index) : name);
        return Var(index, var_names_.back(), this);
    }

    // 添加约束
    void addConstraint(const Constraint& constr) {
        LinearExpr expr = constr.getExpr();
        constraint_matrix_.appendRow(expr.getIndices().size(), expr.getIndices().data(),
                                   expr.getCoeffs().data());
        row_lb_.push_back(constr.getLowerBound());
        row_ub_.push_back(constr.getUpperBound());
    }

    // 设置优化方向
    void setMaximize(bool maximize = true) {
        is_maximization_ = maximize;
    }

    // 求解
    bool solve() {
        solver_.addColumns(obj_coeffs_.size(), var_lb_.data(), var_ub_.data(),
                          obj_coeffs_.data(), NULL, NULL);
        solver_.addRows(row_lb_.size(), row_lb_.data(), row_ub_.data(),
                       constraint_matrix_.getElements(), constraint_matrix_.getIndices(),
                       constraint_matrix_.getVectorStarts(), constraint_matrix_.getVectorLengths());
        solver_.setOptimizationDirection(is_maximization_ ? -1 : 1);
        solver_.primal();
        return solver_.isProvenOptimal();
    }

    // 获取结果
    double getVarValue(const Var& v) const {
        return solver_.primalColumnSolution()[v.getIndex()];
    }

    double getObjectiveValue() const {
        return is_maximization_ ? -solver_.objectiveValue() : solver_.objectiveValue();
    }

    void printSolution() const {
        if (!solver_.isProvenOptimal()) {
            std::cout << "No optimal solution found." << std::endl;
            return;
        }
        std::cout << "Optimal solution found!" << std::endl;
        for (size_t i = 0; i < var_names_.size(); ++i) {
            std::cout << var_names_[i] << " = " << solver_.primalColumnSolution()[i] << std::endl;
        }
        std::cout << "Objective value = " << getObjectiveValue() << std::endl;
    }
};

// 重载运算符以支持约束语法
Constraint operator<=(const LinearExpr& expr, double rhs) {
    return Constraint(expr, -COIN_DBL_MAX, rhs);
}

Constraint operator>=(const LinearExpr& expr, double rhs) {
    return Constraint(expr, rhs, COIN_DBL_MAX);
}

Constraint operator==(const LinearExpr& expr, double rhs) {
    return Constraint(expr, rhs, rhs);
}

// 示例使用
int main() {
    Model model;

    // 添加变量
    Var x1 = model.addVar(0.0, COIN_DBL_MAX, 3.0, "x1");
    Var x2 = model.addVar(0.0, COIN_DBL_MAX, 2.0, "x2");

    // 添加约束：2x1 + x2 <= 4
    LinearExpr expr1 = 2.0 * x1 + x2;
    model.addConstraint(expr1 <= 4.0);

    // 添加约束：x1 + 2x2 <= 4
    LinearExpr expr2 = x1 + 2.0 * x2;
    model.addConstraint(expr2 <= 4.0);

    // 设置最大化
    model.setMaximize(true);

    // 求解
    if (model.solve()) {
        model.printSolution();
    } else {
        std::cout << "Failed to solve the model." << std::endl;
    }

    return 0;
}