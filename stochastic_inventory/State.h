//
// Created by Zhen Chen on 2025/2/28.
//

#ifndef STATE_H
#define STATE_H

#include <boost/functional/hash.hpp>

class State {
  int period{}; // c++11, {} 值初始化，默认为 0
  double initialInventory{};

public:
  State();

  explicit State(int period, double initialInventory);

  [[nodiscard]] double getInitialInventory() const;

  [[nodiscard]] int getPeriod() const;

  void print() const;

  // hashmap must define operator == and a struct to compute hash
  bool operator==(const State &other) const {
    // 需要定义 `==`
    // const MyClass &other	保证 other 参数不可修改
    // const 在函数结尾 保证当前对象(this) 不可修改
    // 不会修改成员变量的方法 都可以在函数声明的结尾添加 const
    return period == other.period && initialInventory == other.initialInventory;
  }

  // 允许哈希结构体访问私有成员
  // friend struct
  friend struct std::hash<State>;

  // define operator < or give a self defined comparator for sorting map
  bool operator<(const State &other) const;

  friend std::ostream &operator<<(std::ostream &os, const State &state);
};

// `std::hash<State>` 需要特化
// 一般放到头文件，否则出错
template <>
// 当你为自定义类（比如 MyClass）提供 std::hash 的特化时，
// 你并不是定义一个全新的类，而是对已有的模板类 std::hash
// 进行特化（specialization）。 C++ 要求特化一个模板时，使用 template<>
// 语法，表示这是一个针对特定类型的特化版本， 而不是一个普通的模板定义。
struct std::hash<State> {
  // size_t 表示无符号整数
  size_t operator()(const State &s) const noexcept {
    // noexcept 表示这个函数不会抛出异常
    // boost 的哈希计算更安全
    std::size_t seed = 0;
    boost::hash_combine(seed, s.period);
    boost::hash_combine(seed, s.initialInventory);
    return seed;

    // return std::hash<int>()(s.period) ^
    // std::hash<double>()(s.initialInventory) << 1; // 计算哈希值
    // std::hash<int>() 是一个 std::hash<int> 类型的对象，调用 () 运算符可以计算
    // obj.id（整数）的哈希值
    // ^（异或）是位运算，不会造成进位，适合合并多个哈希值
    // 这里的 << 1 左移 1 位（相当于乘
    // 2），让哈希值更加分散，避免简单叠加导致哈希冲突
  }
};

#endif // STATE_H

// //下面的结构体若要正确编译哈希，在声明 unordered_map 时，必须显式指定
// `StateHash` 作为第三个模板参数
// // 自定义哈希结构体计算类的哈希
// struct StateHash {
//     // size_t 表示无符号整数
//     std::size_t operator()(const State &state) const {
//         // boost 的哈希计算更安全
//         std::size_t seed = 0;
//         boost::hash_combine(seed, state.period);
//         boost::hash_combine(seed, state.initialInventory);
//         return seed;
//
//         // return std::hash<int>()(state.period) ^
//         std::hash<double>()(state.initialInventory) << 1;
//         // // std::hash<int>() 是一个 std::hash<int> 类型的对象，调用 ()
//         运算符可以计算 obj.id（整数）的哈希值
//         // // ^（异或）是位运算，不会造成进位，适合合并多个哈希值
//         // // 这里的 << 1 左移 1 位（相当于乘
//         2），让哈希值更加分散，避免简单叠加导致哈希冲突
//     }
// };
