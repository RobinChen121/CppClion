/*
 * Created by Zhen Chen on 2025/3/15.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#include "CashLeadtimeState.h"

double CashLeadtimeState::getQpre() const { return Qpre; }

std::ostream &operator<<(std::ostream &os, const CashLeadtimeState &state) {
  os << "Period: " << state.getPeriod()
     << ", ini inventory: " << state.getInitialInventory()
     << ", ini cash: " << state.getIniCash()
     << ", Q in the last period: " << state.getQpre() << std::endl;
}
