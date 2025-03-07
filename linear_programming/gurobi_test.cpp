/*
 * Created by Zhen Chen on 2025/3/7.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */

#include <iostream>
#include "gurobi_c++.h"

int main() {
    try {
        // 创建 Gurobi 环境
        GRBEnv env = GRBEnv();
        env.set(GRB_IntParam_OutputFlag, 0); // 启用输出

        // 创建模型
        GRBModel model = GRBModel(env);
        model.set(GRB_StringAttr_ModelName, "Production_Optimization");

        // 添加决策变量
        GRBVar xA = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "x_A"); // 产品 A
        GRBVar xB = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "x_B"); // 产品 B

        // 设置目标函数：maximize 30x_A + 40x_B
        GRBLinExpr objective = 30.0 * xA + 40.0 * xB;
        model.setObjective(objective, GRB_MAXIMIZE);

        // 添加约束
        // 约束 1: x_A + 2x_B <= 100
        GRBLinExpr constr1 = xA + 2.0 * xB;
        model.addConstr(constr1 <= 100, "Resource1");

        // 约束 2: 3x_A + x_B <= 150
        GRBLinExpr constr2 = 3.0 * xA + xB;
        model.addConstr(constr2 <= 150, "Resource2");

        // 优化模型
        model.optimize();

        // 检查优化状态
        int status = model.get(GRB_IntAttr_Status);
        if (status == GRB_OPTIMAL) {
            std::cout << "Optimal solution found:\n";
            std::cout << "x_A = " << xA.get(GRB_DoubleAttr_X) << "\n";
            std::cout << "x_B = " << xB.get(GRB_DoubleAttr_X) << "\n";
            std::cout << "Objective value = " << model.get(GRB_DoubleAttr_ObjVal) << "\n";
        } else {
            std::cout << "No optimal solution found. Status = " << status << "\n";
        }
    } catch (GRBException e) {
        std::cout << "Gurobi error code = " << e.getErrorCode() << "\n";
        std::cout << e.getMessage() << "\n";
    } catch (...) {
        std::cout << "Unknown error during optimization\n";
    }

    return 0;
}
