//
// Created by Zhen Chen on 2025/2/26.
// 40 periods, maxQ 150, value is 1359, time is 4.61s
// 40 periods, maxQ 100, value is 1351, time is 3.03s
//

#include "Newsvendor.h"
#include <chrono>
#include <iostream>
#include "ProbabilityMassFunctions.h"
#include <limits>
#include <future>

NewsvendorDP::NewsvendorDP(const size_t T, const int capacity,
                           const double stepSize, const double fixOrderCost,
                           const double unitVariOrderCost,
                           const double unitHoldCost, const double unitPenaltyCost,
                           const double truncatedQuantile, const double max_I,
                           const double min_I,
                           std::vector<std::vector<std::vector<double> > > pmf): T(static_cast<int>(T)),
    capacity(capacity),
    stepSize(stepSize),
    fixOrderCost(fixOrderCost),
    unitVariOrderCost(unitVariOrderCost),
    unitHoldCost(unitHoldCost), unitPenaltyCost(unitPenaltyCost), truncatedQuantile(truncatedQuantile),
    max_I(max_I), min_I(min_I), pmf(std::move(pmf)) {
};


std::vector<double> NewsvendorDP::feasibleActions() const {
    const int QNum = static_cast<int>(capacity / stepSize);
    std::vector<double> actions(QNum);
    for (int i = 0; i < QNum; i = i + 1) {
        actions[i] = i * stepSize;
    }
    return actions;
}

State NewsvendorDP::stateTransitionFunction(const State &state, const double action, const double demand) const {
    double nextInventory = state.getInitialInventory() + action - demand;
    if (state.getPeriod() == 1) {
        (void) nextInventory;
    }
    if (nextInventory > 0) {
        (void) nextInventory;
    }
    nextInventory = nextInventory > max_I ? max_I : nextInventory;
    nextInventory = nextInventory < min_I ? min_I : nextInventory;

    const int nextPeriod = state.getPeriod() + 1;
    // C++11 引入了统一的列表初始化（Uniform Initialization），鼓励使用大括号 {} 初始化类
    const auto newState = State{nextPeriod, nextInventory};

    return newState;
}

double NewsvendorDP::immediateValueFunction(const State &state, const double action, const double demand) const {
    const double fixCost = action > 0 ? fixOrderCost : 0;
    const double variCost = action * unitVariOrderCost;
    double nextInventory = state.getInitialInventory() + action - demand;
    nextInventory = nextInventory > max_I ? max_I : nextInventory;
    nextInventory = nextInventory < min_I ? min_I : nextInventory;
    const double holdCost = std::max(unitHoldCost * nextInventory, 0.0);
    const double penaltyCost = std::max(-unitPenaltyCost * nextInventory, 0.0);

    const double totalCost = fixCost + variCost + holdCost + penaltyCost;
    return totalCost;
}

double NewsvendorDP::getOptAction(const State &state) {
    return cacheActions[state];
}

auto NewsvendorDP::getTable() const {
    size_t stateNums = cacheActions.size();
    std::vector<std::vector<double> > table(stateNums, std::vector<double>(3));
    int index = 0;
    for (const auto &[fst, snd]: cacheActions) {
        table[index][0] = fst.getPeriod();
        table[index][1] = fst.getInitialInventory();
        table[index][2] = snd;
        index++;
    }
    return table;
}

double NewsvendorDP::recursion(const State &state) {
    double bestQ = 0.0;
    double bestValue = std::numeric_limits<double>::max();
    const std::vector<double> actions = feasibleActions();
    for (const double action: feasibleActions()) {
        double thisValue = 0;
        for (auto demandAndProb: pmf[state.getPeriod() - 1]) {
            thisValue += demandAndProb[1] * immediateValueFunction(state, action, demandAndProb[0]);
            if (state.getPeriod() < T) {
                auto newState = stateTransitionFunction(state, action, demandAndProb[0]);
                (void) action;
                if (cacheValues.contains(newState)) {
                    // some issues here
                    thisValue += demandAndProb[1] * cacheValues[newState];
                } else {
                    thisValue += demandAndProb[1] * recursion(newState);
                }
            }
        }
        if (thisValue < bestValue) {
            bestValue = thisValue;
            bestQ = action;
        }
    }
    cacheActions[state] = bestQ;
    cacheValues[state] = bestValue;
    return bestValue;
}

// 在recursion函数中使用并行计算
double NewsvendorDP::recursion_parallel(const State &state) {
    double bestQ = 0.0;
    double bestValue = std::numeric_limits<double>::max();
    const std::vector<double> actions = feasibleActions();

    DpResult result;
    result.valueFunction.resize(T + 1);
    result.policy.resize(T);

    // 使用std::vector来存储future对象
    std::vector<std::future<std::pair<double, double> > > futures;

    for (const double action: actions) {
        // 使用std::async来并行计算每个action的值
        double thisValue = 0;
        for (auto demandAndProb: pmf[state.getPeriod() - 1]) {
            thisValue += demandAndProb[1] * immediateValueFunction(state, action, demandAndProb[0]);
            if (state.getPeriod() < T) {
                auto newState = stateTransitionFunction(state, action, demandAndProb[0]);
                if (cacheValues.contains(newState)) {
                    thisValue += demandAndProb[1] * cacheValues[newState];
                } else {
                    auto future = std::async(std::launch::async, &NewsvendorDP::recursion_parallel, this, newState);
                    thisValue += demandAndProb[1] * future.get();
                }
            }
        }
        if (thisValue < bestValue) {
            bestValue = thisValue;
            bestQ = action;
        }
    }

    std::lock_guard<std::mutex> lock(cacheMutex);
    cacheValues[state] = bestValue;
    cacheActions[state] = bestQ;
    return bestValue;
}


int main() {
    std::vector<double> demands(40, 20);
    const std::string distribution_type = "poisson";
    constexpr int capacity = 150; // maximum ordering quantity
    constexpr double stepSize = 1.0;
    constexpr double fixOrderCost = 0;
    constexpr double unitVariOderCost = 1;
    constexpr double unitHoldCost = 2;
    constexpr double unitPenaltyCost = 10;
    constexpr double truncQuantile = 0.9999; // truncated quantile for the demand distribution
    constexpr double maxI = 500; // maximum possible inventory
    constexpr double minI = -300; // minimum possible inventory


    const auto pmf = ProbabilityMassFunctions(truncQuantile, stepSize, distribution_type).getPMF(demands);
    const size_t T = demands.size();
    auto model1 = NewsvendorDP(T, capacity, stepSize, fixOrderCost, unitVariOderCost, unitHoldCost, unitPenaltyCost,
                               truncQuantile, maxI, minI, pmf);

    auto initialState = State(1, 0);
    auto start_time = std::chrono::high_resolution_clock::now();
    auto optValue = model1.recursion(initialState);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "planning horizon is " << T << " periods" << std::endl;
    std::cout << "running time of C++ in sequential is " << duration << std::endl;
    std::cout << "Final optimal value is: " << optValue << std::endl;

//    auto model2 = NewsvendorDP(T, capacity, stepSize, fixOrderCost, unitVariOderCost, unitHoldCost, unitPenaltyCost,
//                               truncQuantile, maxI, minI, pmf);
//    start_time = std::chrono::high_resolution_clock::now();
//    optValue = model2.recursion_parallel(initialState);
//    end_time = std::chrono::high_resolution_clock::now();
//    duration = end_time - start_time;
//    std::cout << std::string(30, '*') << std::endl;
//    std::cout << "planning horizon is " << T << " periods" << std::endl;
//    std::cout << "running time of C++ in parallel is " << duration << std::endl;
//    std::cout << "Final optimal value is: " << optValue << std::endl;
//    const auto optQ = model2.getOptAction(initialState);
//    std::cout << "Optimal Q is: " << optQ << std::endl;
//    auto table = model2.getTable();

    return 0;
}
