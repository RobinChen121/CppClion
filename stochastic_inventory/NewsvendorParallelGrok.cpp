//
// Created by Zhen Chen on 2025/3/3.
// parallel computing for newsvendor.
// 40 periods, maxQ 150, value is 1351, time is 2.171s.(8 threads)
// backward recursion, several threads, each thread loops between an invenrory invterval
// make it easier for parallel computing.
// 这个程序使用 map 相对于 unordered_map 速度慢了至少1倍

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
    static constexpr int T = 40; // 时间阶段数
    static constexpr double C_ORDER = 1.0; // 单位订购成本
    static constexpr double C_HOLDING = 2.0; // 单位持有成本
    static constexpr double C_SHORTAGE = 10.0; // 单位缺货成本
    static constexpr double FIXED_COST = 0.0; // 每次订购的固定成本
    static constexpr int MAX_INVENTORY = 150; // 最大库存容量
    static constexpr double DEMAND_LAMBDA = 20.0; // 泊松分布的均值（lambda）
    static constexpr int NUM_THREADS = 8; // 并行线程数

    std::mutex mtx; // 互斥锁保护共享数据写入

    // 泊松分布的 PMF
    static double poissonPMF(int k) {
        const double logP = -DEMAND_LAMBDA + k * std::log(DEMAND_LAMBDA) - std::lgamma(k + 1);
        return std::exp(logP);
    }

    // 阶段成本的期望值（解析计算）
    static double expectedStageCost(double inventoryBefore, double order) {
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

        const double orderCost = (order > 0) ? FIXED_COST + C_ORDER * order : 0;
        return holding + shortage + orderCost;
    }

    // 并行计算单个阶段的动态规划
    void computeStage(int t, int startInv, int endInv,
                      std::vector<std::map<int, double> > &valueFunction,
                      std::vector<std::map<int, int> > &policy) {
        for (int i = startInv; i < endInv; ++i) {
            double minCost = std::numeric_limits<double>::infinity();
            int bestOrder = 0;

            const int maxOrder = MAX_INVENTORY - std::max(0, i);

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
                // emplace_back 是 std::vector 提供的一个成员函数，用于在向量末尾直接构造一个新对象，
                // 而不是先创建对象再插入（相比 push_back 更高效）
                // this 表示当前对象的指针，说明这段代码出现在 MultiStageNewsboy 类的一个成员函数中
                // 在 C++ 中，调用非静态成员函数需要一个对象实例，
                // 因为成员函数隐式地有一个 this 参数，用于访问对象的成员变量或方法。
                // std::thread 的构造函数需要一个可调用对象及其参数。
                // 对于成员函数，第一个参数必须是对象（通过指针或引用传递），这就是为什么需要 this。
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
