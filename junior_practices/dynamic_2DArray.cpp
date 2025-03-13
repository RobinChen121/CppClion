//
// Created by Zhen Chen on 2025/2/26.
//

#include <iostream>
#include <vector>
using namespace std;

// 传递 `vector<vector<int>>`
void print2DArray(const vector<vector<int> > &arr) {
  for (const auto &row: arr) {
    for (const int num: row) {
      cout << num << " ";
    }
    cout << endl;
  }
}

int main() {
  const vector<vector<int> > arr = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  print2DArray(arr);
  const int rows = 3;
  const int cols = 4;
  const std::vector<std::vector<int> > vec(rows, std::vector<int>(cols, 0));
  print2DArray(vec);
  const vector<int> v1 = {1, 2, 3};
  const vector v2(4, v1);
  print2DArray(v2);

  return 0;
}
