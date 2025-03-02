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

// int main() {
//     // std::map<State, float, CompareState> stateMap;
//     // std::unordered_map<State, float> stateMap;
//     std::map<State, float> stateMap;
//     stateMap[State(1, 2.0)] = 5.0;
//     stateMap[State(1, 1.0)] = 3.0;
//     stateMap[State(1, 3.0)] = 4.0;
//     stateMap[State(0, 3.0)] = 4.0;
//     stateMap[State(0, 4.0)] = 4.0;
//     stateMap[State(0, 3.0)] = 4.0;
//     stateMap[State(0, 2.0)] = 4.0;
//
//     std::cout << stateMap[State(1, 2.0)] << " " << stateMap[State(1, 3.0)] << std::endl;
//
//
//     return 0;
// }
