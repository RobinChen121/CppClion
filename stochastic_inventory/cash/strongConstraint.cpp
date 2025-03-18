/*
 * Created by Zhen Chen on 2025/3/13.
 * Email: chen.zhen5526@gmail.com
 * Description: 6 periods running time 12.91s, while java is 20.28s on mac book
 * pro m1.
 *
 *
 */

#include "../../utils/PMF.h"
#include "../states/CashState.h"
#include <chrono>
#include <cstddef> // for size_t
#include <iostream>
#include <ostream>
#include <vector>

class StrongConstraint {
private:
  double ini_inventory = 0;
  double ini_cash = 100;
  CashState ini_state = CashState(1, ini_inventory, ini_cash);
  std::vector<double> demands = {10, 10, 10, 10};
  std::string distribution_type = "poisson";
  size_t T = demands.size(); // 直接获取大小

  std::vector<double> prices = std::vector<double>(T, 10.0);
  std::vector<double> fixed_order_costs = std::vector<double>(T, 0.0);
  std::vector<double> unit_vari_order_costs = std::vector<double>(T, 1.0);
  std::vector<double> unit_hold_costs = std::vector<double>(T, 0.0);
  std::vector<double> overhead_costs = std::vector<double>(T, 0.0);
  double unit_salvage_value = 0.5;
  double deposit_rate = 0; // deposit interest rate

  double step_size = 1;
  double order_capacity = 100;
  double truncated_quantile = 0.9999;
  double max_inventory = 200;
  double min_inventory = 0;
  double max_cash = 2000;
  double min_cash = 0;

  const std::vector<std::vector<std::vector<double>>> pmf =
      PMF(truncated_quantile, step_size, distribution_type).getPMF(demands);
  std::unordered_map<CashState, double> cacheActions;
  std::unordered_map<CashState, double> cacheValues;

public:
  [[nodiscard]] std::vector<double>
  feasibleActions(const CashState &state) const {
    const double cashQ =
        state.getIniCash() / unit_vari_order_costs[state.getPeriod()];
    const double QBound = std::min(order_capacity, cashQ);
    const int QNum = static_cast<int>(QBound / step_size);

    std::vector<double> actions(QNum);
    for (int i = 0; i < QNum; i = i + 1) {
      actions[i] = i * step_size;
    }
    return actions;
  }

  [[nodiscard]] CashState
  stateTransitionFunction(const CashState &state, const double action,
                          const double randomDemand) const {
    double nextInventory =
        std::max(0.0, state.getInitialInventory() + action - randomDemand);
    double nextCash = state.getIniCash() +
                      immediateValueFunction(state, action, randomDemand);
    nextCash = nextCash > max_cash ? max_cash : nextCash;
    nextCash = nextCash < min_cash ? min_cash : nextCash;
    nextInventory =
        nextInventory > max_inventory ? max_inventory : nextInventory;
    nextInventory =
        nextInventory < min_inventory ? min_inventory : nextInventory;
    // cash is integer or not
    nextCash =
        std::round(nextCash * 10) / 10.0; // the right should be a decimal
    return CashState{state.getPeriod() + 1, nextInventory, nextCash};
  }

  [[nodiscard]] double immediateValueFunction(const CashState &state,
                                              const double action,
                                              const double randomDemand) const {
    int t = state.getPeriod() - 1;
    const double revenue =
        prices[t] *
        std::min(state.getInitialInventory() + action, randomDemand);
    const double fixedCost = action > 0 ? fixed_order_costs[t] : 0;
    const double variableCost = unit_vari_order_costs[t] * action;
    const double deposit =
        (state.getIniCash() - fixedCost - variableCost) * (1 + deposit_rate);
    const double inventoryLevel =
        state.getInitialInventory() + action - randomDemand;
    const double holdCosts = unit_hold_costs[t] * std::max(inventoryLevel, 0.0);
    double cash_increment =
        revenue + deposit - holdCosts - overhead_costs[t] - state.getIniCash();
    const double salValue =
        state.getPeriod() == T
            ? unit_salvage_value * std::max(inventoryLevel, 0.0)
            : 0;
    cash_increment += salValue;
    return cash_increment;
  }

  double recursion(const CashState &state) { // NOLINT(*-no-recursion)
    double bestQ = 0.0;
    double bestValue = std::numeric_limits<double>::lowest();
    for (const std::vector<double> actions = feasibleActions(state);
         const double action : actions) {
      double thisValue = 0;
      for (auto demandAndProb : pmf[state.getPeriod() - 1]) {
        thisValue += demandAndProb[1] *
                     immediateValueFunction(state, action, demandAndProb[0]);
        if (state.getPeriod() < T) {
          auto newState =
              stateTransitionFunction(state, action, demandAndProb[0]);
          if (cacheValues.contains(newState)) {
            // some issues here
            thisValue += demandAndProb[1] * cacheValues[newState];
          } else {
            thisValue += demandAndProb[1] * recursion(newState);
          }
        }
      }
      if (thisValue > bestValue) {
        bestValue = thisValue;
        bestQ = action;
      }
    }
    cacheActions[state] = bestQ;
    cacheValues[state] = bestValue;
    return bestValue;
  }

  double solve() { return recursion(ini_state); }
};

int main() {
  auto strongConstraint = StrongConstraint();
  const auto start_time = std::chrono::high_resolution_clock::now();
  const double final_value = strongConstraint.solve();
  const auto end_time = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double> duration = end_time - start_time;
  std::cout << "running time is " << duration << std::endl;
  std::cout << "Final expected cash increment is " << final_value << std::endl;
}