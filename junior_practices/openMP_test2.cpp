/*
 * Created by Zhen Chen on 2025/3/6.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */
#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>  // 用于测量时间
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision; // 包含 cpp_int
// cpp_int 会降低计算速度，没有 long long 快

using namespace std;
using namespace std::chrono;

int main() {
    const int N = 1000000000; // 10 亿个元素，并行计算加速约 9 倍
    vector<int> data(N, 1); // 创建大小为 N，所有元素初始化为 1 的数组

    long long sum_serial = 0, sum_parallel = 0;

    // 1️⃣ **串行计算**
    auto start_serial = high_resolution_clock::now(); // 记录开始时间
    for (int i = 0; i < N; i++) {
        sum_serial += i * i;
    }
    auto end_serial = high_resolution_clock::now(); // 记录结束时间
    auto duration_serial = duration_cast<milliseconds>(end_serial - start_serial);

    cout << "Serial Sum: " << sum_serial << endl;
    cout << "Serial Execution Time: " << duration_serial.count() << " ms\n" << endl;

    // 2️⃣ **并行计算**
    // 默认情况下，OpenMP 会自动使用 CPU 可用的最大线程数
    // 可通过 omp_set_num_threads(4);  强制设置线程数
    auto start_parallel = high_resolution_clock::now();
    // 定义一个归约操作（reduction），对变量 sum_parallel 执行加法（+）累加。
    // 确保每个线程的局部结果最终合并为全局结果，避免数据竞争。
#pragma omp parallel for reduction(+:sum_parallel)
    for (int i = 0; i < N; i++) {
        sum_parallel += i * i;
    }
    auto end_parallel = high_resolution_clock::now();
    auto duration_parallel = duration_cast<milliseconds>(end_parallel - start_parallel);

    cout << "Parallel Sum: " << sum_parallel << endl;
    cout << "Parallel Execution Time: " << duration_parallel.count() << " ms\n" << endl;

    // **计算加速比**
    double speedup = (double) duration_serial.count() / duration_parallel.count();
    cout << "Speedup Factor: " << speedup << "x" << endl;

    return 0;
}
