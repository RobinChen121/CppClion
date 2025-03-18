/*
 * Created by Zhen Chen on 2025/3/13.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#include "RemoveDuplicates.h"

#include <iostream>
#include <unordered_set>

Matrix removeDuplicateRows(const Matrix &mat) {
  std::unordered_set<std::vector<double>, VectorHash> uniqueRows(mat.begin(),
                                                                 mat.end());
  // 用哈希表去重
  return {uniqueRows.begin(), uniqueRows.end()};
}

// int main() {
//   const Matrix mat = {
//       {1, 2, 3},
//       {4, 5, 6},
//       {1, 2, 3}, // 重复行
//       {7, 8, 9},
//       {4, 5, 6} // 重复行
//   };
//
//   const Matrix uniqueMat = removeDuplicateRows(mat);
//
//   std::unordered_set<std::vector<double>, VectorHash> sets;
//   std::vector<double> first_row = {10, 12, 43};
//   std::vector<double> second_row(3, 20);
//   std::vector<double> third_row(3, 20);
//   sets.insert(first_row);
//   sets.insert(second_row);
//
//   std::cout << "Matrix after removing duplicate rows:\n";
//   for (const auto &row : uniqueMat) {
//     for (const double val : row) {
//       std::cout << val << " ";
//     }
//     std::cout << std::endl;
//   }
//
//   std::cout << "sets:\n";
//   for (const auto &row : sets) {
//     for (const double val : row) {
//       std::cout << val << " ";
//     }
//     std::cout << std::endl;
//   }
//
//   return 0;
// }
