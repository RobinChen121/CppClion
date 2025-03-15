/*
 * Created by Zhen Chen on 2025/3/13.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#include "RemoveDuplicates.h"

#include <boost/functional/hash.hpp>
#include <iostream>
#include <unordered_set>

// 自定义哈希函数
struct VectorHash {
    size_t operator()(const std::vector<double> &v) const {
        std::size_t seed = 0;
        for (const double num : v) {
            boost::hash_combine(seed, v);
        }
        return seed;
    }
};

Matrix removeDuplicateRows(const Matrix &mat) {
    std::unordered_set<std::vector<double>, VectorHash> uniqueRows(mat.begin(),
                                                                   mat.end());
    // 用哈希表去重
    return {uniqueRows.begin(), uniqueRows.end()};
}

// int main() {
//     const Matrix mat = {
//         {1, 2, 3},
//         {4, 5, 6},
//         {1, 2, 3}, // 重复行
//         {7, 8, 9},
//         {4, 5, 6} // 重复行
//     };
//
//     const Matrix uniqueMat = removeDuplicateRows(mat);
//
//     std::cout << "Matrix after removing duplicate rows:\n";
//     for (const auto &row : uniqueMat) {
//         for (const double val : row) {
//             std::cout << val << " ";
//         }
//         std::cout << std::endl;
//     }
//     return 0;
// }
