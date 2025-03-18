/*
 * Created by Zhen Chen on 2025/3/12.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#ifndef CASHSTATE_H
#define CASHSTATE_H

#include "State.h"

class CashState : public State {
  double initialCash{};

public:
  CashState(const int period, const double initialInventory,
            const double initialCash)
      : State(period, initialInventory), initialCash(initialCash) {};

  double getIniCash() const;

  friend std::ostream &operator<<(std::ostream &os, const CashState &state);

  // hashmap must define operator == and a struct to compute hash
  bool operator==(const CashState &other) const {
    // 需要定义 `==`
    // const MyClass &other	保证 other 参数不可修改
    // const 在函数结尾 保证当前对象(this) 不可修改
    // 不会修改成员变量的方法 都可以在函数声明的结尾添加 const
    return getPeriod() == other.getPeriod() &&
           getInitialInventory() == other.getInitialInventory() &&
           initialCash == other.initialCash;
  }

  // friend std::ostream &operator<<(std::ostream &os, const CashState &other) {
  //     os<<"Period: "<< other.getPeriod() << ", ini inventory:
  //     "<<other.getInitialInventory()<< "ini cash: "<<
  //     other.getIniCash()<<std::endl;
  // }
};

template <> // 表示模版特化， override 标准库中的 hash
            // 生成函数，必须有，否则出错
            // 一般放到头文件，否则出错
struct std::hash<CashState> {
  // size_t 表示无符号整数
  size_t operator()(const CashState &s) const noexcept {
    // noexcept 表示这个函数不会抛出异常
    // boost 的哈希计算更安全
    std::size_t seed = 0;
    boost::hash_combine(seed, s.getPeriod());
    boost::hash_combine(seed, s.getInitialInventory());
    boost::hash_combine(seed, s.getIniCash());
    return seed;
  }
};

#endif // CASHSTATE_H
