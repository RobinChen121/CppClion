/*
 * Created by Zhen Chen on 2025/3/21.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#include "CashLeadtimeMultiState.h"

#include <iostream>
#include <ostream>

bool CashLeadtimeMultiState::operator==(
    const CashLeadtimeMultiState &other) const {
  return period == other.period && ini_I1 == other.ini_I1 &&
         ini_I2 == other.ini_I2 && Qpre1 == other.Qpre1 &&
         Qpre2 == other.Qpre2 && iniCash == other.iniCash;
}

std::ostream &operator<<(std::ostream &os,
                         const CashLeadtimeMultiState &state) {
  os << "Period: " << state.period << ", ini inventory1: " << state.ini_I1
     << ", ini inventory2: " << state.ini_I2 << ", Qpre1: " << state.Qpre1
     << ", Qpre2: " << state.Qpre2 << ", ini cash: " << state.iniCash
     << std::endl;
}

// int main() {
//   const CashLeadtimeMultiState state{1, 10, 45, 10, 5, 0};
//   std::cout << state;
//
//   return 0;
// }