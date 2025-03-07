/*
 * Created by Zhen Chen on 2025/3/7.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *  #pragma omp parallel sections are very slow like async
 */

#include <iostream>
#include <omp.h>
#include <chrono>
#include <unordered_map>
using namespace std;

// 使用 unordered_map 缓存 Fibonacci 计算结果
unordered_map<int, long long> cache;

long long parallel_fib_omp(int n) {
    if (n <= 1) return n;

    if (cache.contains(n)) {
        return cache[n];
    }

    long long x, y;
    // x = parallel_fib_omp(n - 1);
    // y = parallel_fib_omp(n - 2);

#pragma omp parallel sections
    {
#pragma omp section
        x = parallel_fib_omp(n - 1);


#pragma omp section
        y = parallel_fib_omp(n - 2);
    }
    return x + y;
}

int main() {
    constexpr int n = 40;
    omp_set_num_threads(4); // 设置 OpenMP 线程数
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Fibonacci(" << n << ") = " << parallel_fib_omp(n) << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "running time is of parallel computing is " << duration << std::endl;

    return 0;
}

