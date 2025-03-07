/*
 * Created by Zhen Chen on 2025/3/6.
 * Email: chen.zhen5526@gmail.com
 * Description: test the paralle of OpenMp.
 *
 *
 */
#include <iostream>
#include <omp.h>

#include <iostream>
#include <omp.h>

int main() {
    std::cout << "Max threads: " << omp_get_max_threads() << "\n";
#pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            std::cout << "Running threads: " << omp_get_num_threads() << "\n";
        }
    }
    return 0;
}
