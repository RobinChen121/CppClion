/*
 * Created by Zhen Chen on 2025/3/13.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */

#ifndef SAMPLING_H
#define SAMPLING_H

#include <string>
#include <iostream>

class Sampling {
private:
  std::string distName = "poisson";
  double mean;

  void checkName();

public:
  explicit Sampling(const std::string &name, const double mean): distName(name), mean(mean) {
    checkName();
  }

  Sampling();

  void print() const { std::cout << distName << std::endl; };

  // 在 C++ 中，static 成员函数是属于类本身，而不是类的对象的。
  // 这意味着它们可以在不创建类实例的情况下被调用，
  // 并且不能访问 非静态成员变量 或 非静态成员函数，因为它们不依赖于具体对象。
  static double poissonCDF(int k, double lambda);

  static int poissonQuantile(double p, double lambda);

  std::vector<double> generateSamples(int sampleNum) const;

  static int randInt(int a, int b);

  static std::vector<std::vector<int> > generateScenarioPaths(int scenarioNum,
                                                              const std::vector<int> &sampleNums);
};


#endif //SAMPLING_H
