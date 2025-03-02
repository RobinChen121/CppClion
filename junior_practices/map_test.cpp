//
// Created by Zhen Chen on 2025/2/27.
//

#include <iostream>
#include <map>

int main() {
  std::map<std::string, int> myMap;
  myMap["apple"] = 5;          // 添加 key="apple"，value=5
  myMap.insert({"apple", 10}); // 如果 key 已经存在，insert() 不会修改它的值。

  for (const auto &[fst, snd] : myMap) {
    std::cout << fst << ": " << snd << std::endl;
  }
  return 0;
}