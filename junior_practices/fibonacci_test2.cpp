//
// Created by Zhen Chen on 2025/2/23.
//

#include <iostream>
#include <chrono>
using namespace std;


// Recursive Fibonacci
long long fibRecursive(int n) {
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Iterative Fibonacci
long long fibIterative(int n) {
    long long a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        long long temp = a + b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    fibRecursive(40);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "C++ recursive Fibonacci time: " << duration.count() << " seconds" << endl;

    start = chrono::high_resolution_clock::now();
    fibIterative(30);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "C++ iterative Fibonacci time: " << duration.count() << " seconds" << endl;

    return 0;
}