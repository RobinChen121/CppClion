//
// Created by Zhen Chen on 2025/2/26.
//

#include "dynamic_2DArray.h"
#include <iostream>
#include <vector>
using namespace std;

// 传递 `vector<vector<int>>`
void print2DArray(const vector<vector<int>>& arr) {
    for (const auto& row : arr) {
        for (const int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int print_2Dtest() {
    const vector<vector<int>> arr = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    print2DArray(arr);
    return 0;
}