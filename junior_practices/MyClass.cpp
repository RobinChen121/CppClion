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

// ostream 是一个输出流的类， std::cout 是其一个实例
// & 表示引用传递，而不是值传递
// 返回类型是 std::ostream&，表示函数需要返回一个对 std::ostream 对象的引用。
// 参数 os 已经是一个引用（std::ostream& os），它绑定到调用时传入的实际流对象（如 std::cout）
// 非 const 引用不能绑定到临时对象
// 在 C++ 中，临时对象具有短暂的生命周期，通常在表达式结束时销毁，添加 const 可延长其寿命
std::ostream &operator <<(std::ostream &os, const MyClass &c) {
    os << c.value << " of this class" << std::endl; // 访问私有成员
    os << "test";
    return os;
}

int main() {
    const MyClass test(10);
    std::cout << MyClass(11) << std::endl;
    std::cout << test << std::endl;
    return 0;
}

