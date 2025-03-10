/*
 * Created by Zhen Chen on 2025/3/9.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */

#ifndef VAR_H
#define VAR_H

#include <iostream>

// 前向声明 Model 类，避免两个类循环互相导入
class Model;

// 表示变量的类
class Var {
private:
    int index_;
    std::string name_;
    Model *model_;

public:
    // Var(int idx, const std::string& n, Model* m) : index_(idx), name_(n), model_(m) {}
    Var(int idx, const std::string &n, Model *m);

    int getIndex() const { return index_; }
    std::string getName() const { return name_; }
};

#endif //VAR_H
