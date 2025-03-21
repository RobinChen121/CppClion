/*
 * Created by Zhen Chen on 2025/3/21.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#include "../states/CashLeadtimeMultiState.h"

#include <algorithm>
#include <vector>

class OverdraftLeadtimeMultiProduct {
private:
  double ini_inventory1 = 0.0;
  double ini_inventory2 = 0.0;
  double ini_cash = 0.0;
  double ini_Qpre1 = 0.0;
  double ini_Qpre2 = 0.0;

  CashLeadtimeMultiState ini_state{1,         ini_inventory1, ini_inventory2,
                                   ini_Qpre1, ini_Qpre2,      ini_cash};

  std::vector<double> demands1 = {20.0, 20.0, 20.0, 20.0};
  size_t T = demands1.size(); // 直接获取大小
  std::vector<double> demands2 = std::vector<double>(T);
  std::string distribution_type = "poisson";

  std::vector<double> prices1 = std::vector<double>(T, 10.0);
  std::vector<double> prices2 = std::vector<double>(T, 5.0);

public:
  // std::transform
  // 需要在运行时执行，而类的成员变量必须在构造函数的初始化列表或构造函数体内初始化
  // 因此 transform 不能在类的私有属性中使用
  OverdraftLeadtimeMultiProduct() {
    std::ranges::transform(demands1, demands2.begin(),
                           [](const double x) { return x / 2; });
  }
};

int main() {
  std::vector<double> demands1 = {20, 20, 20, 20};
  const size_t T = demands1.size(); // 直接获取大小
  std::vector<double> demands2(T);
  std::ranges::transform(demands1, demands2.begin(),
                         [](const double x) { return x / 2; });

  return 0;
}