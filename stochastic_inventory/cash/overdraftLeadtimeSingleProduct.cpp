/*
 * Created by Zhen Chen on 2025/3/15.
 * Email: chen.zhen5526@gmail.com
 * Description: For 3 period, c++ is faster than java, but for 4 period, it is
 * lower (over 120s vs 41s in java). The main reason lies in the recursion for
 * double hash map. If round the cash in recursion, running time is about 9s
 * while java is still 41s; rounding 1 decimal, running time is about 60s; no
 * rounding, running time is 128s. Java's JIT seems to optimize some
 * computations: after running the DP sometimes in Java, its result becomes not
 * related with the number of decimals.
 *
 * 5 periods, rounding with 0 decimal, running time is 60.5s.
 * {15, 15, 15, 15, 15}, rounding with 1 decimal, running time is 876.99s,
 * final value is 250.998, opt Q at period 1 is 24.
 *
 *
 */
#include "../../utils/PMF.h"
#include "../states/CashLeadtimeState.h"

#include <boost/unordered_map.hpp>
#include <chrono>
#include <iostream>
#include <vector>

class OverdraftLeadtimeSingleProduct {
private:
  double ini_inventory = 0;
  double ini_cash = 0;
  CashLeadtimeState ini_state =
      CashLeadtimeState{1, ini_inventory, ini_cash, 0.0};
  static constexpr std::vector<double> demands = {15, 15, 15, 15, 15};
  std::string distribution_type = "poisson";
  static constexpr size_t T = demands.size(); // 直接获取大小

  std::vector<double> prices = std::vector<double>(T, 10.0);
  // std::vector<double> fixed_order_costs = std::vector<double>(T, 0.0);
  std::vector<double> unit_vari_order_costs = std::vector<double>(T, 1.0);
  // std::vector<double> unit_hold_costs = std::vector<double>(T, 0.0);
  std::vector<double> overhead_costs = std::vector<double>(T, 50.0);
  double unit_salvage_value = 0.5; //  * unit_vari_order_costs[T - 1];

  double r0 = 0.0;
  double r1 = 0.1;
  double r2 = 2.0;
  double overdraft_limit = 500;

  double max_order_quantity = 30.0;
  double truncated_quantile = 0.9999;
  double step_size = 1.0;
  double min_inventory = 0;
  double max_inventory = 60;
  double min_cash = -200;
  double max_cash = 300;

  const std::vector<std::vector<std::vector<double>>> pmf =
      PMF(truncated_quantile, step_size, distribution_type).getPMF(demands);
  std::unordered_map<CashLeadtimeState, double> cacheActions;
  std::unordered_map<CashLeadtimeState, double> cacheValues;

public:
  [[nodiscard]] std::vector<double> feasibleActions() const {
    const int QNum = static_cast<int>(max_order_quantity / step_size);

    std::vector<double> actions(QNum);
    for (int i = 0; i < QNum; i = i + 1) {
      actions[i] = i * step_size;
    }
    return actions;
  }

  [[nodiscard]] double immediateValueFunction(const CashLeadtimeState &state,
                                              const double action,
                                              const double randomDemand) const {
    const int t = state.getPeriod() - 1;
    const double revenue =
        prices[t] *
        std::min(state.getInitialInventory() + state.getQpre(), randomDemand);
    const double variableCost = unit_vari_order_costs[t] * action;
    const double inventoryLevel =
        state.getInitialInventory() + state.getQpre() - randomDemand;
    const double cash_before_interest =
        state.getIniCash() - variableCost - overhead_costs[t];
    double interest = 0;
    if (cash_before_interest > 0.0) {
      interest = cash_before_interest * r0;
    } else if (-overdraft_limit < cash_before_interest &&
               cash_before_interest < 0.0) {
      interest = cash_before_interest * r1;
    } else {
      interest =
          -overdraft_limit * r1 + (cash_before_interest - overdraft_limit) * r2;
    }
    const double cash_after_interest =
        cash_before_interest + interest + revenue;
    double cash_increment = cash_after_interest - state.getIniCash();
    const double salValue =
        state.getPeriod() == T
            ? unit_salvage_value * std::max(inventoryLevel, 0.0)
            : 0;
    cash_increment += salValue;
    return cash_increment;
  }

  [[nodiscard]] CashLeadtimeState
  stateTransitionFunction(const CashLeadtimeState &state, const double action,
                          const double randomDemand) const {
    double nextInventory = std::max(0.0, state.getInitialInventory() +
                                             state.getQpre() - randomDemand);
    const double nextQpre = action;
    double nextCash = state.getIniCash() +
                      immediateValueFunction(state, action, randomDemand);
    nextCash = nextCash > max_cash ? max_cash : nextCash;
    nextCash = nextCash < min_cash ? min_cash : nextCash;
    nextInventory =
        nextInventory > max_inventory ? max_inventory : nextInventory;
    nextInventory =
        nextInventory < min_inventory ? min_inventory : nextInventory;
    // cash is integer or not
    nextCash = std::round(nextCash * 10) / 10.0; // the right should be a
    // decimal
    return CashLeadtimeState{state.getPeriod() + 1, nextInventory, nextCash,
                             nextQpre};
  }

  double recursion(const CashLeadtimeState &state) { // NOLINT(*-no-recursion)
    double bestQ = 0.0;
    double bestValue = std::numeric_limits<double>::lowest();
    for (const std::vector<double> actions = feasibleActions();
         const double action : actions) {
      double thisValue = 0.0;
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

  std::vector<double> solve() {
    return {recursion(ini_state), cacheActions.at(ini_state)};
  }
};

int main() {
  auto problem = OverdraftLeadtimeSingleProduct();
  const auto start_time = std::chrono::high_resolution_clock::now();
  const auto final_value = problem.solve()[0];
  const auto end_time = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double> duration = end_time - start_time;
  std::cout << "running time is " << duration << std::endl;
  std::cout << "Final expected cash increment is " << final_value << std::endl;
  std::cout << "Optimal Q in the first period is " << problem.solve()[1]
            << std::endl;
}