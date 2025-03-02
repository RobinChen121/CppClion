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

    system("gnuplot -e \"plot 'data.txt' with lines title 'y=sin(x)'; pause -1\"");
    return 0;
}
