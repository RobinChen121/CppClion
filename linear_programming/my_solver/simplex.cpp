/*
 * Created by Zhen Chen on 2025/3/8.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */

#include "simplex.h"
#include <iostream>
#include <iomanip>

constexpr double M = 10000;

// 单纯形法实现
// Bland 规则确保单纯形法不会在退化解之间循环，最终会收敛到最优解或检测到无界解
// Bland 必须同时应用到换入和换出
int Simplex::findPivotColumn() const {
    int pivotCol = -1;
    for (int j = 0; j < cols - 1; j++) {
        // 从索引 0 开始检查
        if (tableau[0][j] < 0) {
            if (pivotCol == -1 || j < pivotCol) {
                pivotCol = j; // 选择索引最小的负检验数
            }
        }
    }
    return pivotCol;
}

// Bland 规则确保单纯形法不会在退化解之间循环，最终会收敛到最优解或检测到无界解
int Simplex::findPivotRow(const int pivotCol) const {
    int pivotRow = -1;
    double minRatio = std::numeric_limits<double>::max();
    for (int i = 1; i < rows; i++) {
        if (tableau[i][pivotCol] > 1e-6) {
            // 避免数值误差
            if (const double ratio = tableau[i][cols - 1] / tableau[i][pivotCol]; ratio < minRatio) {
                // 严格小于，确保唯一性
                minRatio = ratio;
                pivotRow = i;
            } else if (abs(ratio - minRatio) < 1e-6) {
                // 比率相等时选最小索引
                if (basicVars[i - 1] < basicVars[pivotRow - 1]) {
                    pivotRow = i;
                }
            }
        }
    }
    return pivotRow;
}

void Simplex::pivot(const int pivotRow, int pivotCol) {
    const double pivotValue = tableau[pivotRow][pivotCol];
    for (int j = 0; j < cols; j++) {
        tableau[pivotRow][j] /= pivotValue;
    }
    for (int i = 0; i < rows; i++) {
        if (i != pivotRow) {
            const double factor = tableau[i][pivotCol];
            for (int j = 0; j < cols; j++) {
                tableau[i][j] -= factor * tableau[pivotRow][j];
            }
        }
    }
    // 更新基变量：新进入变量替换旧基变量
    basicVars[pivotRow - 1] = pivotCol;
}

Simplex::Simplex(const std::vector<std::vector<double> > &initialTableau) {
    tableau = initialTableau;
    rows = static_cast<int>(tableau.size());
    cols = static_cast<int>(tableau[0].size());
    initializeBasicVariables(); // 初始化基变量
}

void Simplex::solve() {
    displayTableau();
    initializeObjective();
    while (true) {
        const int pivotCol = findPivotColumn();
        if (pivotCol == -1) break; // 已达到最优解
        const int pivotRow = findPivotRow(pivotCol);
        if (pivotRow == -1) {
            std::cout << "无界解" << std::endl;
            return;
        }
        pivot(pivotRow, pivotCol);
    }
    displaySolution();
}

// 判断某列是否为基变量，并返回对应的行（如果不是基变量，返回 -1）
int Simplex::isBasicVariable(const int col) const {
    int basicRow = -1;
    for (int i = 1; i < rows; i++) {
        if (abs(tableau[i][col] - 1.0) < 1e-6) {
            // 检查是否为 1
            if (basicRow == -1) {
                basicRow = i;
            } else {
                return -1; // 出现多个 1，非基变量
            }
        } else if (abs(tableau[i][col]) > 1e-6) {
            // 检查是否有非 0 值
            return -1; // 非 0 非 1，非基变量
        }
    }
    return basicRow; // 返回对应的基行
}

void Simplex::displaySolution() const {
    std::cout << "最优值: " << -tableau[0][cols - 1] << std::endl;
    std::cout << "最终基变量及其值:\n";
    for (int i = 0; i < basicVars.size(); i++) {
        const int col = basicVars[i];
        std::cout << "x" << (col + 1) << " = " << tableau[i + 1][cols - 1] << std::endl;
    }
    for (int j = 0; j < cols - 1; j++) {
        if (find(basicVars.begin(), basicVars.end(), j) == basicVars.end()) {
            std::cout << "x" << (j + 1) << " = 0" << std::endl;
        }
    }
}

// 初始化基变量
void Simplex::initializeBasicVariables() {
    basicVars.resize(rows - 1, -1);
    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < cols - 1; j++) {
            if (isBasicVariable(j) == i) {
                basicVars[i - 1] = j;
                break;
            }
        }
    }
}

// 初始化目标函数（消除人工变量的M项）
void Simplex::initializeObjective() {
    for (int j = 0; j < cols - 1; j++) {
        if (tableau[0][j] == -M) {
            // 识别人工变量列
            for (int i = 1; i < rows; i++) {
                if (tableau[i][j] == 1) {
                    // 该人工变量是基变量
                    constexpr double factor = M;
                    for (int k = 0; k < cols; k++) {
                        // 大M 法第一行通过行变换将人工变量的系数转化为0
                        tableau[0][k] += factor * tableau[i][k];
                    }
                }
            }
        }
    }
}

void Simplex::displayTableau() const {
    std::cout << "当前单纯形表:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << tableau[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "当前基变量: ";
    for (const int var: basicVars) {
        std::cout << "x" << (var + 1) << " ";
    }
    std::cout << std::endl << std::endl;
}


int main() {
    // 初始化单纯形表
    // 目标函数: max z = 2x1 + 3x2 转换为 -2x1 - 3x2 + z = 0
    // 约束: 2x1 + x2 + s1 = 4
    //       x1 + 2x2 + s2 = 5
    const std::vector<std::vector<double> > tableau = {
        {-2, -3, 0, 0, 0}, // 目标函数 -3x1 - 2x2 + z = 0
        {2, 1, 1, 0, 4}, // 约束1
        {1, 2, 0, 1, 5} // 约束2
    };

    Simplex simplex(tableau);
    simplex.solve();
    std::cout << "****************************" << std::endl;

    //初始化单纯形表
    // 目标函数: max z = 2x1 + 3x2 转换为 -2x1 - 3x2 + M*a1 + M*a2 + z = 0
    // 约束: x1+x2 >= 2, i.e.,  x1 + x2 - s1 + a1 = 2
    //      2x1+x2 = 4, i.e., 2x1 + x2 + a2 = 4
    const std::vector<std::vector<double> > tableau2 = {
        {-2, -3, 1, -M, -M, 0}, // 目标函数 (x1, x2, s1, a1, a2, z)
        {1, 1, -1, 1, 0, 2}, // 约束1
        {2, 1, 0, 0, 1, 4} // 约束2
    };
    Simplex simplex2(tableau2);
    simplex2.solve();

    std::cout << "****************************" << std::endl;
    // test recycling
    //maximize z = (3/4)x1 -20x2 + (1/2)x3 -6x4 subject to
    // (1 / 4)x1 - 8x2 - x3 + 9x4 <= 0
    // (1 / 2)x1 - 12x2 - (1 / 2)x3 + 3x4 <= 0
    // x3 <= 1
    const std::vector<std::vector<double> > tableau3 = {
        {-3.0 / 4, 20, -1.0 / 2, 6, 0, 0, 0, 0}, // 目标函数
        {1.0 / 4, -8, -1, 9, 1, 0, 0, 0}, // 约束1
        {1.0 / 2, -12, -1.0 / 2, 3, 0, 1, 0, 0}, // 约束2
        {0, 0, 1, 0, 0, 0, 1, 1} // 约束3
    };

    Simplex simplex3(tableau3);
    simplex3.solve();

    return 0;
}
