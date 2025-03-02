//
// Created by Zhen Chen on 2025/2/26.
//

#ifndef NEWSVENDORDP_H
#define NEWSVENDORDP_H

#include "State.h"
#include <unordered_map>
#include <map>

// struct CompareState;

class NewsvendorDP {
    int T;
    int capacity;
    double stepSize;
    double fixOrderCost;
    double unitVariOrderCost;
    double unitHoldCost;
    double unitPenaltyCost;
    double truncatedQuantile;
    double max_I;
    double min_I;

    std::vector<std::vector<std::vector<double> > > pmf;

    // std::unordered_map<State, double> cacheActions{};
    // std::unordered_map<State, double> cacheValues{};

    // std::map<State, double, CompareState> cacheActions{};
    // std::map<State, double, CompareState> cacheValues{};

    std::map<State, double> cacheActions{};
    std::map<State, double> cacheValues{};

public:
    NewsvendorDP(size_t T, int capacity, double stepSize, double fixOrderCost, double unitVariOrderCost,
                 double unitHoldCost, double unitPenaltyCost, double truncatedQuantile, double max_I, double min_I,
                 std::vector<std::vector<std::vector<double> > > pmf);

    [[nodiscard]] std::vector<double> feasibleActions() const;

    [[nodiscard]] State stateTransitionFunction(const State &state, double action, double demand) const;

    [[nodiscard]] double immediateValueFunction(const State &state, double action, double demand) const;

    [[nodiscard]] double getOptAction(const State &tate);

    [[nodiscard]] auto getTable() const;

    double recursion(const State &state);
};

// ✅ 自定义比较器，没啥用，不如在 state.h 里面重载 <
// struct CompareState {
//     bool operator()(const State &p1, const State &p2) const {
//         if (p1.getPeriod() < p2.getPeriod()) {
//             return true;
//         }
//         if (p1.getPeriod() == p2.getPeriod()) {
//             if (p1.getInitialInventory() < p2.getInitialInventory()) {
//                 return true;
//             }
//             return false;
//         }
//         return false;
//     }
// };

#endif //NEWSVENDORDP_H
