//
// Created by Zhen Chen on 2025/2/22.
//

#include <iostream>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include <future>

using namespace std;
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision; // 包含 cpp_int


// 使用 unordered_map 缓存 Fibonacci 计算结果
unordered_map<int, cpp_int> cache;
std::mutex cacheMutex; // std::mutex named cacheMutex is used to ensure that access to the cache is thread-safe.

// Compute Fibonacci by parallel
cpp_int fibonacci_parallel(int n) {
    // 基本情况
    if (n == 0) return 0;
    if (n == 1) return 1;

    std::lock_guard<std::mutex> lock1(std::mutex cacheMutex);
    // 检查缓存中是否已经计算过
    if (cache.find(n) != cache.end()) {
        return cache[n];
    }

    // 使用 std::async 并行计算两个子问题
    // std::async does not provide a built-in mechanism to limit the number of threads.
    // By default, std::async will create a new thread for each task if you use std::launch::async.
    auto future1 = std::async(std::launch::async, fibonacci_parallel, n - 1);
    auto future2 = std::async(std::launch::async, fibonacci_parallel, n - 2);

    // 获取结果
    cpp_int result = future1.get() + future2.get(); {
        std::lock_guard<std::mutex> lock2(cacheMutex);
        // 缓存结果
        cache[n] = result;
    }

    return result;
}

// Compute Fibonacci by sequential
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
    int n = 100;

    // get the number of threads
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) {
        std::cout << "Unable to determine the number of threads." << std::endl;
    } else {
        std::cout << "Number of concurrent threads supported: " << numThreads << std::endl;
    }

    // 计算并输出结果
    auto start = std::chrono::high_resolution_clock::now();
    cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "running time is of sequential computing is " << duration << std::endl;

    // 这个并行计算没啥优势，std::async 每次递归创建新线程，开销随深度增加。
    // auto start = std::chrono::high_resolution_clock::now();
    // cout << "Fibonacci(" << n << ") = " << fibonacci_parallel(n) << endl;
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration = end - start;
    // std::cout << "running time is of parallel computing is " << duration << std::endl;


    return 0;
}
