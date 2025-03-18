/*
 * Created by Zhen Chen on 2025/3/16.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#include "selfHash.h"

#include <boost/functional/hash.hpp> // boost::hash_combine
#include <iostream>
#include <ostream>

// method 1
// 自定义哈希函数，用于多个浮点数组合哈希
template <typename T> struct float_hash {
  std::size_t operator()(T f) const {
    const std::int64_t bits = *reinterpret_cast<std::int64_t *>(&f);
    return std::hash<std::int64_t>()(bits);
  }
};

// 组合多个哈希值
template <typename... Args> std::size_t combine_hash(Args... args) {
  return (
      0 ^ ... ^
      (float_hash<std::decay_t<Args>>()(args))); // 使用折叠表达式进行异或操作
}

// method 3: by boost
template <typename T1, typename T2>
std::size_t hash_combine_boost(const T1 &v1, const T2 &v2) {
  std::size_t seed = 0;
  boost::hash_combine(seed, std::hash<T1>{}(v1));
  boost::hash_combine(seed, std::hash<T2>{}(v2));
  return seed;
}

// int main() {
//   constexpr int x = 10;
//   constexpr double y = 30;
//   constexpr double z = 30.5;
//   constexpr double w = 30.538;
//
//   std::cout << "method 3 boost:" << std::endl;
//   auto combined_hash1 = hash_combine_boost(x, y);
//   auto combined_hash2 = hash_combine_boost(x, z);
//   auto combined_hash3 = hash_combine_boost(x, w);
//   std::cout << combined_hash1 << std::endl;
//   std::cout << combined_hash2 << std::endl;
//   std::cout << combined_hash3 << std::endl;
//
//   std::cout << "method 2 variadic...:" << std::endl;
//   combined_hash1 = hash_combine(x, y);
//   combined_hash2 = hash_combine(x, z);
//   combined_hash3 = hash_combine(x, w);
//   std::cout << combined_hash1 << std::endl;
//   std::cout << combined_hash2 << std::endl;
//   std::cout << combined_hash3 << std::endl;
// }