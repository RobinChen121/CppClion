// /*
//  * Created by Zhen Chen on 2025/3/6.
//  * Email: chen.zhen5526@gmail.com
//  * Description: there are errors for this library
//  *
//  *
//  */
// #include "matplotlibcpp.h"
// #include <vector>
// #include <cmath>
//
// namespace plt = matplotlibcpp;
//
// int main() {
//     std::vector<double> x, y;
//
//     for (double i = -10; i <= 10; i += 0.1) {
//         x.push_back(i);
//         y.push_back(sin(i));  // y = sin(x)
//     }
//
//     plt::plot(x, y);
//     plt::title("y = sin(x)");
//     plt::xlabel("x");
//     plt::ylabel("y");
//     plt::grid(true);
//     plt::show();  // 显示图像
//
//     return 0;
// }
//
