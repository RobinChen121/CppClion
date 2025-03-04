//
// Created by Zhen Chen on 2025/3/3.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define T 30                    // 时间阶段数
#define C_ORDER 1.0            // 单位订购成本
#define C_HOLDING 2.0          // 单位持有成本
#define C_SHORTAGE 10.0        // 单位缺货成本
#define FIXED_COST 0.0        // 每次订购的固定成本
#define MAX_INVENTORY 100      // 最大库存容量
#define DEMAND_LAMBDA 20.0     // 泊松分布的均值（lambda）
#define NUM_THREADS 8          // 并行线程数

// 全局数据结构
typedef struct {
    double** valueFunction; // V[t][inventory]
    int** policy;           // policy[t][inventory]
    int invSize;            // 库存范围大小
} DpResult;

typedef struct {
    int t;                  // 当前阶段
    int startInv;           // 库存起始
    int endInv;             // 库存结束
    DpResult* result;       // 计算结果
} ThreadArg;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 计算泊松分布 PMF
double poissonPMF(int k) {
    double logP = -DEMAND_LAMBDA + k * log(DEMAND_LAMBDA) - lgamma(k + 1);
    return exp(logP);
}

// 阶段成本的期望值
double expectedStageCost(double inventoryBefore, double order) {
    int s = (int)round(inventoryBefore + order);
    if (s < 0) s = 0;

    double holding = 0.0;
    for (int d = 0; d <= s; ++d) {
        holding += (s - d) * poissonPMF(d);
    }
    holding *= C_HOLDING;

    double shortage = 0.0;
    for (int d = s + 1; d <= MAX_INVENTORY * 2; ++d) {
        shortage += (d - s) * poissonPMF(d);
    }
    shortage *= C_SHORTAGE;

    double orderCost = (order > 0) ? FIXED_COST + C_ORDER * order : 0;
    return holding + shortage + orderCost;
}

// 真实阶段成本（模拟用）
double stageCost(double inventoryBefore, double order, double demand) {
    double inventoryAfter = inventoryBefore + order - demand;
    double holdingCost = C_HOLDING * (inventoryAfter > 0 ? inventoryAfter : 0);
    double shortageCost = C_SHORTAGE * (inventoryAfter < 0 ? -inventoryAfter : 0);
    double orderCost = (order > 0) ? FIXED_COST + C_ORDER * order : 0;
    return holdingCost + shortageCost + orderCost;
}

// 并行计算单个阶段
void* computeStage(void* arg) {
    ThreadArg* data = (ThreadArg*)arg;
    int t = data->t;
    int startInv = data->startInv;
    int endInv = data->endInv;
    DpResult* result = data->result;
    int offset = MAX_INVENTORY; // 将库存范围映射到 [0, 2*MAX_INVENTORY]

    for (int i = startInv; i < endInv; ++i) {
        double minCost = INFINITY;
        int bestOrder = 0;
        int maxOrder = MAX_INVENTORY - (i > 0 ? i : 0);

        for (int order = 0; order <= maxOrder; ++order) {
            double currentCost = expectedStageCost(i, order);
            int s = (int)round(i + order);

            double nextCost = 0.0;
            for (int nextInv = -MAX_INVENTORY; nextInv <= MAX_INVENTORY; ++nextInv) {
                int demand = s - nextInv;
                if (demand >= 0) {
                    double prob = poissonPMF(demand);
                    nextCost += prob * result->valueFunction[t + 1][nextInv + offset];
                }
            }

            double totalCost = currentCost + nextCost;
            if (totalCost < minCost) {
                minCost = totalCost;
                bestOrder = order;
            }
        }

        pthread_mutex_lock(&mutex);
        result->valueFunction[t][i + offset] = minCost;
        result->policy[t][i + offset] = bestOrder;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// 动态规划主函数
DpResult multiStageNewsboy(double* computationTime) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // 分配内存
    DpResult result;
    result.invSize = 2 * MAX_INVENTORY + 1;
    result.valueFunction = (double**)malloc((T + 1) * sizeof(double*));
    result.policy = (int**)malloc(T * sizeof(int*));
    for (int t = 0; t <= T; ++t) {
        result.valueFunction[t] = (double*)calloc(result.invSize, sizeof(double));
        if (t < T) result.policy[t] = (int*)calloc(result.invSize, sizeof(int));
    }

    // 最后一阶段边界条件
    for (int i = -MAX_INVENTORY; i <= MAX_INVENTORY; ++i) {
        result.valueFunction[T][i + MAX_INVENTORY] = 0.0;
    }

    // 从后向前递推
    for (int t = T - 1; t >= 0; --t) {
        pthread_t threads[NUM_THREADS];
        ThreadArg args[NUM_THREADS];
        int invPerThread = result.invSize / NUM_THREADS;

        for (int threadIdx = 0; threadIdx < NUM_THREADS; ++threadIdx) {
            args[threadIdx].t = t;
            args[threadIdx].startInv = -MAX_INVENTORY + threadIdx * invPerThread;
            args[threadIdx].endInv = (threadIdx == NUM_THREADS - 1) ? MAX_INVENTORY + 1
                                                                   : args[threadIdx].startInv + invPerThread;
            args[threadIdx].result = &result;
            pthread_create(&threads[threadIdx], NULL, computeStage, &args[threadIdx]);
        }

        for (int threadIdx = 0; threadIdx < NUM_THREADS; ++threadIdx) {
            pthread_join(threads[threadIdx], NULL);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    *computationTime = (end.tv_sec - start.tv_sec) * 1000.0 +
                       (end.tv_nsec - start.tv_nsec) / 1000000.0;
    return result;
}

// 模拟函数
void simulate() {
    double dpTime = 0.0;
    DpResult result = multiStageNewsboy(&dpTime);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    double inventory = 0.0;
    double totalCost = 0.0;

    // 使用简单随机数生成泊松需求（近似）
    srand(42);
    double demands[T];
    for (int t = 0; t < T; ++t) {
        // 简单泊松近似（实际应用中需更精确的泊松生成器）
        demands[t] = DEMAND_LAMBDA + (rand() % 10 - 5);
    }

    printf("Multi-Stage Newsboy Model Simulation Results (Poisson, Parallel):\n");
    for (int t = 0; t < T; ++t) {
        int iKey = (int)round(inventory) + MAX_INVENTORY;
        int order = result.policy[t][iKey];
        double demand = demands[t];
        double cost = stageCost(inventory, order, demand);
        totalCost += cost;
        double nextInventory = inventory + order - demand;

        printf("Stage %d: Inventory=%.1f, Order=%d, Demand=%.1f, Cost=%.2f\n",
               t + 1, inventory, order, demand, cost);
        inventory = nextInventory;
    }
    printf("Total Cost: %.2f\n", totalCost);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double simTime = (end.tv_sec - start.tv_sec) * 1000.0 +
                     (end.tv_nsec - start.tv_nsec) / 1000000.0;

    printf("Dynamic Programming Time: %.2f ms\n", dpTime);
    printf("Simulation Time: %.2f ms\n", simTime);

    // 释放内存
    for (int t = 0; t <= T; ++t) {
        free(result.valueFunction[t]);
        if (t < T) free(result.policy[t]);
    }
    free(result.valueFunction);
    free(result.policy);
}

int main() {
    simulate();
    return 0;
}