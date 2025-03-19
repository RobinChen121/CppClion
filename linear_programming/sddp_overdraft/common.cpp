/*
 * Created by Zhen Chen on 2025/3/18.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#include "common.h"
#include <iostream>

PairStatus checkPairStatus(const double end_inventory, const double end_cash,
                           const double overdraft_limit) {
  auto I_status = end_inventory > 0 ? IStatus::POSITIVE : IStatus::NEGATIVE;
  CashStatus cash_status;
  if (end_cash > 0) {
    cash_status = CashStatus::ATW0;
  } else if (end_cash < -overdraft_limit) {
    cash_status = CashStatus::ATW2;
  } else {
    cash_status = CashStatus::ATW1;
  }
  return {I_status, cash_status};
}

// int main() {
//   constexpr auto I_status = IStatus::NEGATIVE;
//   auto cash_status = CashStatus::ATW1;
//
//   std::unordered_map<IStatus, std::array<std::vector<double>, 2>>
//       result_status_last_stage;
//   std::unordered_map<std::pair<IStatus, CashStatus>,
//                      std::array<std::vector<double>, 2>>
//       pair_status;
//
//   // 不能使用 {{}} 初始化
//   const std::array result = {std::vector<double>{12, 23},
//                              std::vector<double>{21, 10.0}};
//   result_status_last_stage[I_status] = result;
//   pair_status[{I_status, cash_status}] = result;
//   for (const auto &arr : result) {
//     for (const auto elem : arr) {
//       std::cout << elem << " ";
//     }
//     std::cout << std::endl;
//   }
//
//   PairStatus result2 = checkPairStatus(-10, -80, 100);
//
//   return 0;
// }