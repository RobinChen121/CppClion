//
// Created by Zhen Chen on 2025/2/28.
//

#include "State.h"
#include <unordered_map>

#include <iostream>
#include <map>

State::State() = default;

State::State(const int period, const double initialInventory): period(period), initialInventory(initialInventory) {
};

double State::getInitialInventory() const {
    return initialInventory;
}

int State::getPeriod() const {
    return period;
}

void State::print() const {
    std::cout << "period: " << period << ", ini I: " << initialInventory << std::endl;
}

// // ✅ 自定义比较器
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