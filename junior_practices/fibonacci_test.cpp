//
// Created by Zhen Chen on 2025/2/22.
//

#include <iostream>
#include <unordered_map>
#include <chrono>
using namespace std;
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision; // 包含 cpp_int

// 使用 unordered_map 缓存 Fibonacci 计算结果
unordered_map<int, cpp_int> cache;

// Fibonacci 函数
cpp_int fibonacci(int n) {
     // 基本情况
     if (n == 0) return 0;
     if (n == 1) return 1;

     // 检查缓存中是否已经计算过
     if (cache.find(n) != cache.end()) {
         return cache[n];
     }

     // 递归计算并缓存结果

     cpp_int result = fibonacci(n - 1) + fibonacci(n - 2);
     cache[n] = result;
     return result;
 }

int main() {
    int n = 12000;

    // 计算并输出结果
    auto start = std::chrono::high_resolution_clock::now();
    cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "running time is " << duration << std::endl;

    return 0;
}