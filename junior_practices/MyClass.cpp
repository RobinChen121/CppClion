//
// Created by Zhen Chen on 2025/2/27.
//

#include "MyClass.h" // 包含头文件

using namespace std;

// 构造函数定义
MyClass::MyClass(const int v) { value = v; }

// showValue 方法的定义
// 不要忘了双冒号之前的类名
void MyClass::showValue() const { cout << "Value: " << value << endl; }
