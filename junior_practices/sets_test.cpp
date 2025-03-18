/*
 * Created by Zhen Chen on 2025/3/17.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */
#include "../utils/removeDuplicates.h"
#include <iostream>
#include <unordered_set>
#include <vector>

int main() {
  std::vector<std::unordered_set<std::vector<double>, VectorHash>>
      cut_coefficients_cache(4);

  cut_coefficients_cache[0].insert({1, 2, 3});
  cut_coefficients_cache[1].insert({1, 2, 3, 4});

  for (size_t i = 0; i < cut_coefficients_cache.size(); ++i) {
    std::cout << "Index " << i << " contains:" << std::endl;
    for (const auto &vec : cut_coefficients_cache[i]) {
      std::cout << "{ ";
      for (double num : vec) {
        std::cout << num << " ";
      }
      std::cout << "}" << std::endl;
    }
  }

  return 0;
}