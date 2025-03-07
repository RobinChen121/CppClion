// 40 periods, maxQ 150, value is 1357.6, time is 10.711s

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono> // 用于计时

class MultiStageNewsboy {
private:
    // 参数
    static const int T = 40;                  // 时间阶段数
    static constexpr double C_ORDER = 1.0;   // 单位订购成本
    static constexpr double C_HOLDING = 2.0; // 单位持有成本
    static constexpr double C_SHORTAGE = 10.0; // 单位缺货成本
    static constexpr double FIXED_COST = 0.0; // 每次订购的固定成本
    static const int MAX_INVENTORY = 150;    // 最大库存容量
    static constexpr double DEMAND_LAMBDA = 20.0; // 泊松分布的均值（lambda）

    // 泊松分布的 PMF 和 CDF
    double poissonPMF(int k) const {
        double logP = -DEMAND_LAMBDA + k * std::log(DEMAND_LAMBDA) - std::lgamma(k + 1);
        return std::exp(logP); // 使用对数形式避免溢出
    }

    double poissonCDF(int k) const {
        double sum = 0.0;
        for (int i = 0; i <= k; ++i) {
            sum += poissonPMF(i);
        }
        return sum;
    }

    // 阶段成本的期望值（解析计算）
    double expectedStageCost(double inventoryBefore, double order) const {
        int s = static_cast<int>(std::round(inventoryBefore + order)); // 订购后的库存水平
        if (s < 0) s = 0; // 确保库存非负

        // 期望持有成本 E[max(0, s - D)]
        double holding = 0.0;
        for (int d = 0; d <= s; ++d) {
            holding += (s - d) * poissonPMF(d);
        }
        holding *= C_HOLDING;

        // 期望缺货成本 E[max(0, D - s)]
        double shortage = 0.0;
        for (int d = s + 1; d <= MAX_INVENTORY * 2; ++d) { // 限制上限避免无限循环
            shortage += (d - s) * poissonPMF(d);
        }
        shortage *= C_SHORTAGE;

        // 订购成本
        double orderCost = (order > 0) ? FIXED_COST + C_ORDER * order : 0;

        return holding + shortage + orderCost;
    }

public:
    struct DpResult {
        std::vector<std::map<int, double>> valueFunction; // V[t][i]
        std::vector<std::map<int, int>> policy;           // policy[t][i]
    };

    DpResult multiStageNewsboy(double& computationTime) {
        auto start = std::chrono::high_resolution_clock::now(); // 开始计时

        DpResult result;
        result.valueFunction.resize(T + 1);
        result.policy.resize(T);

        // 最后一阶段边界条件
        for (int i = -MAX_INVENTORY; i <= MAX_INVENTORY; ++i) {
            result.valueFunction[T][i] = 0.0;
        }

        // 从后向前递推
        for (int t = T - 1; t >= 0; --t) {
            for (int i = -MAX_INVENTORY; i <= MAX_INVENTORY; ++i) {
                double minCost = std::numeric_limits<double>::infinity();
                int bestOrder = 0;

                int maxOrder = MAX_INVENTORY - std::max(0, i);
                for (int order = 0; order <= maxOrder; ++order) {
                    double currentCost = expectedStageCost(i, order);
                    int s = static_cast<int>(std::round(i + order));

                    // 计算下一阶段的期望成本
                    double nextCost = 0.0;
                    for (int nextInv = -MAX_INVENTORY; nextInv <= MAX_INVENTORY; ++nextInv) {
                        int demand = s - nextInv;
                        if (demand >= 0) {
                            double prob = poissonPMF(demand);
                            nextCost += prob * result.valueFunction[t + 1][nextInv];
                        }
                    }

                    double totalCost = currentCost + nextCost;
                    if (totalCost < minCost) {
                        minCost = totalCost;
                        bestOrder = order;
                    }
                }

                result.valueFunction[t][i] = minCost;
                result.policy[t][i] = bestOrder;
            }
        }

        auto end = std::chrono::high_resolution_clock::now(); // 结束计时
        computationTime = std::chrono::duration<double, std::milli>(end - start).count(); // 转换为毫秒
        std::cout << "DP value is " << result.valueFunction[0][0] << "\n";
        return result;
    }

    void simulate() {
        double dpTime = 0.0;
        DpResult result = multiStageNewsboy(dpTime);

        auto start = std::chrono::high_resolution_clock::now(); // 开始模拟计时

        double inventory = 0.0; // 初始库存
        double totalCost = 0.0;

        // 生成泊松分布随机需求用于模拟
        std::mt19937 rng(42);
        std::poisson_distribution<int> dist(DEMAND_LAMBDA);
        std::vector<double> demands(T);
        for (int t = 0; t < T; ++t) {
            demands[t] = dist(rng);
        }

        std::cout << "Multi-Stage Newsboy Model Simulation Results (Poisson):\n";
        for (int t = 0; t < T; ++t) {
            int order = result.policy[t][static_cast<int>(std::round(inventory))];
            double demand = demands[t];
            double cost = stageCost(inventory, order, demand); // 真实成本
            totalCost += cost;
            double nextInventory = inventory + order - demand;

            std::cout << "Stage " << (t + 1) << ": "
                      << "Inventory=" << std::fixed << std::setprecision(1) << inventory
                      << ", Order=" << order
                      << ", Demand=" << demand
                      << ", Cost=" << std::setprecision(2) << cost << "\n";
            inventory = nextInventory;
        }
        std::cout << "Total Cost: " << totalCost << "\n";

        auto end = std::chrono::high_resolution_clock::now(); // 结束模拟计时
        double simTime = std::chrono::duration<double, std::milli>(end - start).count(); // 转换为毫秒

        // 输出运行时间
        std::cout << "Dynamic Programming Time: " << dpTime << " ms\n";
        std::cout << "Simulation Time: " << simTime << " ms\n";
    }

private:
    // 阶段成本函数（用于模拟真实成本）
    double stageCost(double inventoryBefore, double order, double demand) const {
        double inventoryAfter = inventoryBefore + order - demand;
        double holdingCost = C_HOLDING * std::max(0.0, inventoryAfter);
        double shortageCost = C_SHORTAGE * std::max(0.0, -inventoryAfter);
        double orderCost = (order > 0) ? FIXED_COST + C_ORDER * order : 0;
        return holdingCost + shortageCost + orderCost;
    }
};

int main() {
    MultiStageNewsboy model;
    model.simulate();
    return 0;
}