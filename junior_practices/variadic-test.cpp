/*
 * Created by Zhen Chen on 2025/3/17.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */
#include <iostream>

// 可变参数模板函数
template <typename... Args> int sum1(Args... args) {
  return (args + ...); // C++17 折叠表达式
}

// C++17 折叠表达式
template <typename... Args> void print(Args... args) {
  (std::cout << ... << args) << std::endl; // ... 在第二个 << 左边，是左折叠
}

template <typename... Args> auto sum2(Args... args) {
  return (args + ...); // 左折叠，将所有参数求和
}

template <typename... Args> auto subtractLeft(Args... args) {
  return (... - args); // 左折叠，依次进行减法
}

template <typename... Args> auto subtractRight(Args... args) {
  return (args - ...); // 右折叠，依次进行减法
}

// C++11 使用可变参数模板
// 基本函数（终止递归）
void print() { std::cout << "结束" << std::endl; }

// 可变参数模板
template <typename T, typename... Args> // 这个... 表示多种不同的变量类型
void print(T first, Args... rest) {     // 这个... 表示多种不同的变量类型
  std::cout << first << " ";            // 先打印当前参数
  print(rest...); // 递归调用，传入剩余参数, 这个... 表示多种不同的传入参数
}

// sizeof...() 是一个固定用法
template <typename... Args> void printSize(Args... args) {
  std::cout << "Number of arguments: " << sizeof...(Args) << std::endl;
}

int main() {
  std::cout << sum2(1, 2, 3, 4, 5) << std::endl; // 输出: 15
  print(1, 2.5, "Hello", 'A');

  std::cout << subtractLeft(10, 3, 2, 1) << std::endl;
  std::cout << subtractRight(10, 3, 2, 1) << std::endl;

  return 0;
}