/*
 * Created by Zhen Chen on 2025/3/13.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#ifndef REMOVEDUPLICATES_H
#define REMOVEDUPLICATES_H
#include <boost/functional/hash.hpp>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix removeDuplicateRows(const Matrix &mat);

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
#endif // REMOVEDUPLICATES_H
