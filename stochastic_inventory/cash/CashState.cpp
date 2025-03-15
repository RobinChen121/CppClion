/*
 * Created by Zhen Chen on 2025/3/12.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */

#include "CashState.h"

#include <iostream>

double CashState::getIniCash() const {
    return initialCash;
}

std::ostream &operator<<(std::ostream &os, const CashState &state) {
    os << "Period: " << state.getPeriod() << ", ini inventory: " << state.getInitialInventory() <<
            ", ini cash: " << state
            .getIniCash() << std::endl;
}

int main() {
    const CashState state(1, 0, 10);
    std::cout << state << std::endl;
    return 0;
}
