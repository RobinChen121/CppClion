#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>

class MultiStageNewsboy {
private:
    // 参数
    static const int T = 30; // 时间阶段数
    static constexpr double C_ORDER = 1.0; // 单位订购成本
    static constexpr double C_HOLDING = 2.0; // 单位持有成本
    static constexpr double C_SHORTAGE = 10.0; // 单位缺货成本
    static constexpr double FIXED_COST = 0.0; // 每次订购的固定成本
    static const int MAX_INVENTORY = 100; // 最大库存容量
    static constexpr double DEMAND_LAMBDA = 20.0; // 泊松分布的均值（lambda）
    static const int NUM_THREADS = 8; // 并行线程数

    std::mutex mtx; // 互斥锁保护共享数据写入

    // 泊松分布的 PMF
    double poissonPMF(int k) const {
        double logP = -DEMAND_LAMBDA + k * std::log(DEMAND_LAMBDA) - std::lgamma(k + 1);
        return std::exp(logP);
    }

    // 阶段成本的期望值（解析计算）
    double expectedStageCost(double inventoryBefore, double order) const {
        int s = static_cast<int>(std::round(inventoryBefore + order));
        if (s < 0) s = 0;

        double holding = 0.0;
        for (int d = 0; d <= s; ++d) {
            holding += (s - d) * poissonPMF(d);
        }
        holding *= C_HOLDING;

        double shortage = 0.0;
        for (int d = s + 1; d <= MAX_INVENTORY * 2; ++d) {
            shortage += (d - s) * poissonPMF(d);
        }
        shortage *= C_SHORTAGE;

        double orderCost = (order > 0) ? FIXED_COST + C_ORDER * order : 0;
        return holding + shortage + orderCost;
    }

    // 并行计算单个阶段的动态规划
    void computeStage(int t, int startInv, int endInv,
                      std::vector<std::map<int, double> > &valueFunction,
                      std::vector<std::map<int, int> > &policy) {
        for (int i = startInv; i < endInv; ++i) {
            double minCost = std::numeric_limits<double>::infinity();
            int bestOrder = 0;

            int maxOrder = MAX_INVENTORY - std::max(0, i);

            for (int order = 0; order <= maxOrder; ++order) {
                double currentCost = expectedStageCost(i, order);
                int s = static_cast<int>(std::round(i + order));

                double nextCost = 0.0;
                for (int nextInv = -MAX_INVENTORY; nextInv <= MAX_INVENTORY; ++nextInv) {
                    int demand = s - nextInv;
                    if (demand >= 0) {
                        double prob = poissonPMF(demand);
                        nextCost += prob * valueFunction[t + 1][nextInv];
                    }
                }

                double totalCost = currentCost + nextCost;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestOrder = order;
                }
            }

            std::lock_guard<std::mutex> lock(mtx); // 保护共享数据写入
            valueFunction[t][i] = minCost;
            policy[t][i] = bestOrder;
        }
    }

public:
    struct DpResult {
        std::vector<std::map<int, double> > valueFunction; // V[t][inventory]
        std::vector<std::map<int, int> > policy; // policy[t][inventory]
    };

    DpResult multiStageNewsboy(double &computationTime) {
        auto start = std::chrono::high_resolution_clock::now();

        DpResult result;
        result.valueFunction.resize(T + 1);
        result.policy.resize(T);

        // 最后一阶段边界条件
        for (int i = -MAX_INVENTORY; i <= MAX_INVENTORY; ++i) {
            result.valueFunction[T][i] = 0.0;
        }

        // 从后向前递推，使用并行计算
        for (int t = T - 1; t >= 0; --t) {
            std::vector<std::thread> threads;
            int totalInv = 2 * MAX_INVENTORY + 1;
            int invPerThread = totalInv / NUM_THREADS;

            for (int threadIdx = 0; threadIdx < NUM_THREADS; ++threadIdx) {
                int startInv = -MAX_INVENTORY + threadIdx * invPerThread;
                int endInv = (threadIdx == NUM_THREADS - 1)
                                 ? MAX_INVENTORY + 1
                                 : startInv + invPerThread;
                threads.emplace_back(&MultiStageNewsboy::computeStage, this, t, startInv, endInv,
                                     std::ref(result.valueFunction), std::ref(result.policy));
            }

            for (auto &thread: threads) {
                thread.join();
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        computationTime = std::chrono::duration<double, std::milli>(end - start).count();
        std::cout << "DP value is " << result.valueFunction[0][0] << "\n";
        return result;
    }

    void simulate() {
        double dpTime = 0.0;
        DpResult result = multiStageNewsboy(dpTime);

        auto start = std::chrono::high_resolution_clock::now();

        double inventory = 0.0;
        double totalCost = 0.0;

        std::mt19937 rng(42);
        std::poisson_distribution<int> dist(DEMAND_LAMBDA);
        std::vector<double> demands(T);
        for (int t = 0; t < T; ++t) {
            demands[t] = dist(rng);
        }

        std::cout << "Multi-Stage Newsboy Model Simulation Results (Poisson, Parallel):\n";
        for (int t = 0; t < T; ++t) {
            int iKey = static_cast<int>(std::round(inventory));
            int order = result.policy[t][iKey];
            double demand = demands[t];
            double cost = stageCost(inventory, order, demand);
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

        auto end = std::chrono::high_resolution_clock::now();
        double simTime = std::chrono::duration<double, std::milli>(end - start).count();

        std::cout << "Dynamic Programming Time: " << dpTime << " ms\n";
        std::cout << "Simulation Time: " << simTime << " ms\n";
    }

private:
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
