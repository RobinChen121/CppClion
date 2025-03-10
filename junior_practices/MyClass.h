//
// Created by Zhen Chen on 2025/2/27.
//

#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream> // 仅包含需要的库

class MyClass {
private:
  int value;

public:
  explicit MyClass(int v); // 构造函数声明
  void showValue() const; // 成员函数声明
  friend std::ostream &operator <<(std::ostream &os, const MyClass &c);
};

#endif // MYCLASS_H
