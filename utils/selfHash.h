/*
 * Created by Zhen Chen on 2025/3/16.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#ifndef SELFHASH_H
#define SELFHASH_H

#include <functional>

template <typename T> struct float_hash;
template <typename... Args> std::size_t combine_hash(Args... args);

template <typename... Args> std::size_t hash_combine(const Args &...args);

template <typename T, typename... Rest>
void hash_combine_impl(std::size_t &seed, const T &first, const Rest &...rest);
template <typename T> void hash_combine_impl(std::size_t &seed, const T &value);

// method 2
// 递归计算多个变量的哈希
// 递归模板的终止函数
// 位异或操作符 ^ 表示对二进制两个数的每一位进行比较，若对应的位相同则结果为
// 0，若不同则结果为 1
// 0x9e3779b9 是 黄金分割数 phi = (1 + sqrt(5)) / 2 的倒数（乘以 2^32 后的值）。
// 这种常数可以使得哈希值在计算时更加均匀，从而降低哈希冲突的概率。
// seed << 6：这是将 seed 的值向左移动 6 位，相当于乘以 2^6，即
// 64。左移操作常用于快速的位运算，可以增加哈希值的随机性和散列效果。
// seed >> 2：这是将 seed 向右移动 2 位，相当于除以 2^2，即 4。
// 二进制中，第一位表示符号，0位蒸熟，1为负数
// 5 的二进制是 0101，将它左移两位：5 << 2 变成 010100，即 20。
// 左移时，空出的低位会填充为 0。
// 在计算机中，负数 是用 补码（Two's Complement） 来表示的，
// 计算 -20 的二进制补码（假设是 32 位整数）：
// 先求 20 的二进制（正数的原码），20 的二进制（用 32 位表示）：
// 00000000 00000000 00000000 00010100
// 然后求 20 的 反码（对每一位取反，0 变 1，1 变 0）：
// 11111111 11111111 11111111 11101011
// 最后，在反码的基础上 +1，得到补码：
// 11111111 11111111 11111111 11101100
template <typename T>
void hash_combine_impl(std::size_t &seed, const T &value) {
  seed ^= std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T, typename... Rest>
void hash_combine_impl(std::size_t &seed, const T &first, const Rest &...rest) {
  hash_combine_impl(seed, first);
  hash_combine_impl(seed, rest...);
}

// 计算多个变量的哈希
template <typename... Args> std::size_t hash_combine(const Args &...args) {
  std::size_t seed = 0;
  hash_combine_impl(seed, args...);
  return seed;
}
#endif // SELFHASH_H
