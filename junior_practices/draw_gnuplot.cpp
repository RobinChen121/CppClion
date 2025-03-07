//
// Created by Zhen Chen on 2025/2/28.
//

#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    std::ofstream file("data.txt");
    for (double x = -10; x <= 10; x += 0.1) {
        file << x << " " << std::sin(x) << std::endl;
    }
    file.close();

    std::ofstream gnuplotScript("plot_script.gp");
    if (!gnuplotScript) {
        std::cerr << "无法创建 gnuplot 脚本" << std::endl;
        return 1;
    }
    gnuplotScript << "set title 'Scatter Plot'\n";
    gnuplotScript << "set xlabel 'X'\n";
    gnuplotScript << "set ylabel 'Y'\n";
    // 1:2表示第一列作为x轴，第2列作为y轴
    //gnuplotScript << "plot 'data.txt' using 1:2 with lines title 'Data Points'\n"; // line plot
    gnuplotScript << "plot 'data.txt' using 1:2 with points title 'Data Points'\n"; // scatter plot

    // 运行 gnuplot
    system("gnuplot -p plot_script.gp");

    return 0;
}
