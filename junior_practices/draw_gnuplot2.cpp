/*
 * Created by Zhen Chen on 2025/3/7.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <omp.h>

void computeStage(std::vector<double>& valueFunction) {
#pragma omp parallel for
    for (int i = -100; i <= 100; i++) {
        valueFunction[i + 100] = sin(i * 0.1); // 模拟价值函数
    }
}

void plotWithGnuplot(const std::vector<double>& valueFunction) {
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error opening gnuplot pipe\n";
        return;
    }

    // 设置终端和样式
    fprintf(gnuplotPipe, "set terminal qt\n");
    fprintf(gnuplotPipe, "set title 'Value Function'\n");
    fprintf(gnuplotPipe, "set xlabel 'Inventory'\n");
    fprintf(gnuplotPipe, "set ylabel 'Value'\n");
    fprintf(gnuplotPipe, "set grid\n");

    // 在 (0, 0) 添加文字 "Origin"
    fprintf(gnuplotPipe, "set label 'Origin' at 0, 0 center textcolor rgb 'red' font 'Arial,12'\n");

    // 写入数据到临时文件
    FILE *dataFile = fopen("data.txt", "w");
    for (int i = 0; i < valueFunction.size(); i++) {
        fprintf(dataFile, "%d %f\n", i - 100, valueFunction[i]);
    }
    fclose(dataFile);

    // 绘制数据
    fprintf(gnuplotPipe, "plot 'data.txt' with lines title 'Value Function'\n");

    fflush(gnuplotPipe);
    pclose(gnuplotPipe);
}

int main() {
    std::vector<double> valueFunction(201);
    omp_set_num_threads(8);
    computeStage(valueFunction);
    plotWithGnuplot(valueFunction);
    return 0;
}