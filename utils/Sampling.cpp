/*
 * Created by Zhen Chen on 2025/3/13.
 * Email: chen.zhen5526@gmail.com
 * Description:
 *
 *
 */

#include "../utils/Sampling.h"
#include <csignal>
#include <random>
#include <ranges>
#include <vector>

void Sampling::checkName() {
  for (char &c : distName) {
    c = std::tolower(c);
  }
  if (distName != "poisson") {
    std::cout
        << " distribution not found or to do next for this distribution\n";
    raise(-1);
  }
}

// get cumulative distribution function value of Poisson
double Sampling::poissonCDF(const int k, const double lambda) {
  double cumulative = 0.0;
  double term = std::exp(-lambda);
  for (int i = 0; i <= k; ++i) {
    cumulative += term;
    if (i < k)
      term *= lambda / (i + 1); // 递推计算 P(X=i)
  }

  return cumulative;
}

// get inverse cumulative distribution function value of Poisson
int Sampling::poissonQuantile(const double p, const double lambda) {
  int low = 0,
      high = std::max(100, static_cast<int>(lambda * 3)); // 初始搜索区间
  while (low < high) {
    if (const int mid = (low + high) / 2; poissonCDF(mid, lambda) < p) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return low;
}

// 一个 const 函数 通常指的是一个 成员函数，它承诺不会修改类的成员数据
std::vector<double> Sampling::generateSamples(const int sampleNum) const {
  std::vector<double> samples(sampleNum);
  // 创建随机数引擎
  std::random_device rd;  // 随机设备，用来生成随机种子
  std::mt19937 gen(rd()); // 使用 Mersenne Twister 算法的随机数生成器

  for (int i = 0; i < sampleNum; ++i) {
    // 创建均匀分布, LHS sampling
    std::uniform_real_distribution<> dis(static_cast<double>(i) / sampleNum,
                                         (i + 1.0) / sampleNum);
    const double random_value = dis(gen);
    samples[i] = poissonQuantile(random_value, mean);
  }
  return samples;
}

int Sampling::randInt(const int a, const int b) {
  // 创建随机数引擎（使用随机设备作为种子）
  std::random_device rd;
  std::mt19937 gen(rd()); // 使用 Mersenne Twister 作为随机数引擎

  // 定义均匀分布的范围 [a, b]
  std::uniform_int_distribution<int> dist(a, b);

  // 生成并打印一个随机整数
  const int random_number = dist(gen);
  return random_number;
}

std::vector<std::vector<int>>
Sampling::generateScenarioPaths(const int scenarioNum,
                                const std::vector<int> &sampleNums) {
  const size_t T = sampleNums.size();
  std::vector<std::vector<int>> scenarioPaths(scenarioNum);
  for (int i = 0; i < scenarioNum; ++i) {
    scenarioPaths[i].resize(T);
  }

  for (int i = 0; i < scenarioNum; ++i) {
    for (int t = 0; t < T; ++t) {
      scenarioPaths[i][t] = randInt(0, sampleNums[t]);
    }
  }
  return scenarioPaths;
}

template <typename T>
void print2DArray(const std::vector<std::vector<T>> &arr) {
  for (const auto &row : arr) {
    for (const int num : row) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
}

// 按照所有列依次排序
void sortRowsByAllColumns(std::vector<std::vector<int>> &matrix) {
  std::ranges::sort(matrix,
                    [](const std::vector<int> &a, const std::vector<int> &b) {
                      for (size_t i = 0; i < a.size(); ++i) {
                        if (a[i] != b[i])
                          return a[i] < b[i]; // 按列顺序排序
                      }
                      return false; // 所有列都相等
                    });
}

// int main() {
//     const std::string dist = "Poisson";
//     const Sampling sampling(dist, 5);
//     sampling.print();
//     const double lambda = 5.0;
//     const double p = 0.9;
//
//     for (const auto arr = sampling.generateSamples(10); double i : arr) {
//         std::cout << i << " ";
//     }
//     std::cout << std::endl;
//     const auto arr2 = std::vector<int>(5, 10);
//     const std::vector<std::vector<int>> intMatrix = {
//         {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//     print2DArray(intMatrix);
//     std::vector<std::vector<int>> paths =
//         Sampling::generateScenarioPaths(5, arr2);
//     print2DArray(paths);
//     std::cout << std::endl;
//     sortRowsByAllColumns(paths);
//     print2DArray(paths);
//
//     return 0;
// }
