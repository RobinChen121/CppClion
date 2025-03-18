/*
 * Created by Zhen Chen on 2025/3/15.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#ifndef CASHLEADTIMESTATE_H
#define CASHLEADTIMESTATE_H

#include "../../utils/selfHash.h"
#include "CashState.h"

class CashLeadtimeState : public CashState {
private:
  double Qpre = 0;

public:
  CashLeadtimeState(const int period, const double initialInventory,
                    const double iniCash, const double preQ)
      : CashState(period, initialInventory, iniCash), Qpre(preQ) {};
  double getQpre() const;

  // hashmap must define operator == and a struct to compute hash
  bool operator==(const CashLeadtimeState &other) const {
    // 需要定义 `==`
    // const MyClass &other	保证 other 参数不可修改
    // const 在函数结尾 保证当前对象(this) 不可修改
    // 不会修改成员变量的方法 都可以在函数声明的结尾添加 const
    return getPeriod() == other.getPeriod() &&
           getInitialInventory() == other.getInitialInventory() &&
           other.getIniCash() == other.getIniCash() && Qpre == other.Qpre;
  }
  friend std::ostream &operator<<(std::ostream &os,
                                  const CashLeadtimeState &state);

  friend struct std::hash<CashLeadtimeState>;
};

template <> // 表示模版特化， override 标准库中的 hash
            // 生成函数，必须有，否则出错
            // 一般放到头文件，否则出错
struct std::hash<CashLeadtimeState> {
  // size_t 表示无符号整数
  size_t operator()(const CashLeadtimeState &s) const noexcept {
    // noexcept 表示这个函数不会抛出异常
    // boost 的哈希计算更安全
    // std::size_t seed = 0;
    // boost::hash_combine(seed, s.getPeriod());
    // boost::hash_combine(seed, s.getInitialInventory());
    // boost::hash_combine(seed, s.getIniCash());
    // boost::hash_combine(seed, s.Qpre);
    // return seed;

    auto combined_hash = hash_combine(s.getPeriod(), s.getInitialInventory(),
                                      s.getIniCash(), s.getQpre());
    return combined_hash;
  }
};

#endif // CASHLEADTIMESTATE_H
