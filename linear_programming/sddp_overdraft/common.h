/*
 * Created by Zhen Chen on 2025/3/18.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include <array>
#include <unordered_map>
#include <vector>

enum class IStatus { // enum class 相对于 class 更安全，有作用域
  POSITIVE,
  NEGATIVE
};

enum class CashStatus { ATW0, ATW1, ATW2 };

using PairStatus = std::pair<IStatus, CashStatus>;

// 在 C++ 标准库中，std::pair<T1, T2> 已经内置了 operator==，不需要手动重载它
// 自定义哈希函数
template <> struct std::hash<std::pair<IStatus, CashStatus>> {
  size_t operator()(const std::pair<IStatus, CashStatus> &p) const {
    // 哈希计算：使用组合哈希
    const size_t first_hash = hash<int>()(static_cast<int>(p.first));
    const size_t second_hash = hash<int>()(static_cast<int>(p.second));
    return first_hash ^ (second_hash << 1); // 使用异或和位移合并哈希值
  }
}; // namespace std::hash

// self defined hash for pair enum key hashmap
// 这个 hash map 只能局部使用，即必须在定义 map
// 时指定这个hash，不像上一个全局重载 struct pair_hash {
//   template <typename T1, typename T2>
//   std::size_t operator()(const std::pair<T1, T2> &p) const {
//     return std::hash<int>{}(static_cast<int>(p.first)) ^
//            (std::hash<int>{}(static_cast<int>(p.second)) << 1);
//   }
// };

PairStatus checkPairStatus(double end_inventory, double end_cash,
                           double overdraft_limit);
#endif // COMMON_H
