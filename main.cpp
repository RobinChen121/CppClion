//
// Created by Zhen Chen on 2025/2/26.
//

#include <chrono>
#include <iostream>
#include <limits>
#include <boost/functional/hash.hpp>
#include <unordered_map>
#include <iostream>
#include <map>
#include <span>
#include <csignal>

class State {
    int period{}; // c++11, {} 值初始化，默认为 0
    double initialInventory{};

public:
    State();

    explicit State(int period, double initialInventory);

    [[nodiscard]] double getInitialInventory() const;

    [[nodiscard]] int getPeriod() const;

    void print() const;

    // hashmap must define operator == and a struct to compute hash
    bool operator==(const State &other) const {
        // 需要定义 `==`
        // const MyClass &other	保证 other 参数不可修改
        // const 在函数结尾 保证当前对象(this) 不可修改
        // 不会修改成员变量的方法 都可以在函数声明的结尾添加 const
        return period == other.period && initialInventory == other.initialInventory;
    }

    // 允许哈希结构体访问私有成员
    // friend struct
    friend struct std::hash<State>;

    // define operator < or give a self defined comparator for sorting map
    bool operator<(const State &other) const {
        if (period < other.period) {
            return true;
        }
        if (period == other.period) {
            if (initialInventory < other.initialInventory) {
                return true;
            }
            return false;
        }
        return false;
    }
};


// `std::hash<State>` 需要特化
template<> // 表示模版特化， override 标准库中的 hash 生成函数
struct std::hash<State> {
    // size_t 表示无符号整数
    size_t operator()(const State &s) const noexcept {
        // noexcept 表示这个函数不会抛出异常
        // boost 的哈希计算更安全
        std::size_t seed = 0;
        boost::hash_combine(seed, s.period);
        boost::hash_combine(seed, s.initialInventory);
        return seed;

        // return std::hash<int>()(s.period) ^ std::hash<double>()(s.initialInventory) << 1; // 计算哈希值
        // std::hash<int>() 是一个 std::hash<int> 类型的对象，调用 () 运算符可以计算 obj.id（整数）的哈希值
        // ^（异或）是位运算，不会造成进位，适合合并多个哈希值
        // 这里的 << 1 左移 1 位（相当于乘 2），让哈希值更加分散，避免简单叠加导致哈希冲突
    }
};

State::State() = default;

State::State(const int period, const double initialInventory): period(period), initialInventory(initialInventory) {
};

double State::getInitialInventory() const {
    return initialInventory;
}

int State::getPeriod() const {
    return period;
}

void State::print() const {
    std::cout << "period: " << period << ", ini I: " << initialInventory << std::endl;
}


class ProbabilityMassFunctions {
    double truncatedQuantile;
    double stepSize;
    std::string distributionName;

public:
    ProbabilityMassFunctions(double truncatedQuantile, double stepSize, std::string distributionName);

    // std::string getName();

    void checkName() const;

    static double poissonPMF(int k, double lambda);

    [[nodiscard]] std::vector<std::vector<std::vector<double> > > getPMF(std::span<double> demands) const;

    [[nodiscard]] std::vector<std::vector<std::vector<double> > >
    getPMFPoisson(std::span<double> demands) const;

    static int poissonQuantile(double p, double lambda);

    static double poissonCDF(int k, double lambda);
};

// initializing the class
ProbabilityMassFunctions::ProbabilityMassFunctions(
    const double truncatedQuantile, const double stepSize, std::string distributionName)
    : truncatedQuantile(truncatedQuantile), stepSize(stepSize), distributionName(std::move(distributionName)) {
    checkName();
} // std::move for efficiency passing in string and vector

void ProbabilityMassFunctions::checkName() const {
    auto name = distributionName;
    std::ranges::transform(name, name.begin(), ::tolower);
    if (name != "poisson") {
        std::cout << " distribution not found or to do next for this distribution\n";
        raise(-1);
    }
}

// get the probability mass function value of Poisson
double ProbabilityMassFunctions::poissonPMF(const int k, const double lambda) {
    if (k < 0 || lambda <= 0) return 0.0; // 确保参数合法
    return (std::pow(lambda, k) * std::exp(-lambda)) / std::tgamma(k + 1);
    // tgamma(k+1) is a gamma function, 等同于factorial(k)
}


// get cumulative distribution function value of Poisson
double ProbabilityMassFunctions::poissonCDF(const int k, const double lambda) {
    double cumulative = 0.0;
    double term = std::exp(-lambda);
    for (int i = 0; i <= k; ++i) {
        cumulative += term;
        if (i < k)
            term *= lambda / (i + 1); // 递推计算 P(X=i)
    }

    return cumulative;
}

// get inverse cumulative distribution function value of Poisson
int ProbabilityMassFunctions::poissonQuantile(const double p, const double lambda) {
    int low = 0, high = std::max(100, static_cast<int>(lambda * 3)); // 初始搜索区间
    while (low < high) {
        if (const int mid = (low + high) / 2; poissonCDF(mid, lambda) < p) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

// get probability mass function values for each period of Poisson
std::vector<std::vector<std::vector<double> > > ProbabilityMassFunctions::
getPMF(const std::span<double> demands) const {
    if (distributionName == "poisson") {
        return getPMFPoisson(demands);
    }
    return {};
}

// get probability mass function values for each period of Poisson
std::vector<std::vector<std::vector<double> > > ProbabilityMassFunctions::
getPMFPoisson(const std::span<double> demands) const {
    const auto T = demands.size();
    int supportLB[T];
    int supportUB[T];
    for (int i = 0; i < T; ++i) {
        supportUB[i] = poissonQuantile(truncatedQuantile, demands[i]);
        supportLB[i] = poissonQuantile(1 - truncatedQuantile, demands[i]);
    }
    std::vector<std::vector<std::vector<double> > > pmf(T, std::vector<std::vector<double> >());
    for (int t = 0; t < T; ++t) {
        const int demandLength = static_cast<int>((supportUB[t] - supportLB[t] + 1) / stepSize);
        pmf[t] = std::vector<std::vector<double> >(demandLength, std::vector<double>());
        for (int j = 0; j < demandLength; ++j) {
            pmf[t][j] = std::vector<double>(2);
            pmf[t][j][0] = supportLB[t] + j * stepSize;
            const int demand = static_cast<int>(pmf[t][j][0]);
            pmf[t][j][1] = poissonPMF(demand, demands[t]) / (2 * truncatedQuantile - 1);
        }
    }

    return pmf;
}

class NewsvendorDP {
    int T;
    int capacity;
    double stepSize;
    double fixOrderCost;
    double unitVariOrderCost;
    double unitHoldCost;
    double unitPenaltyCost;
    double truncatedQuantile;
    double max_I;
    double min_I;

    std::vector<std::vector<std::vector<double> > > pmf;

     std::unordered_map<State, double> cacheActions{};
     std::unordered_map<State, double> cacheValues{};

//    std::map<State, double> cacheActions{};
//    std::map<State, double> cacheValues{};

public:
    NewsvendorDP(size_t T, int capacity, double stepSize, double fixOrderCost, double unitVariOrderCost,
                 double unitHoldCost, double unitPenaltyCost, double truncatedQuantile, double max_I, double min_I,
                 std::vector<std::vector<std::vector<double> > > pmf);

    [[nodiscard]] std::vector<double> feasibleActions() const;

    [[nodiscard]] State stateTransitionFunction(const State &state, double action, double demand) const;

    [[nodiscard]] double immediateValueFunction(const State &state, double action, double demand) const;

    [[nodiscard]] double getOptAction(const State &tate);

    [[nodiscard]] auto getTable() const;

    double recursion(const State &state);
};

NewsvendorDP::NewsvendorDP(const size_t T, const int capacity,
                           const double stepSize, const double fixOrderCost,
                           const double unitVariOrderCost,
                           const double unitHoldCost, const double unitPenaltyCost,
                           const double truncatedQuantile, const double max_I,
                           const double min_I,
                           std::vector<std::vector<std::vector<double> > > pmf): T(static_cast<int>(T)),
    capacity(capacity),
    stepSize(stepSize),
    fixOrderCost(fixOrderCost),
    unitVariOrderCost(unitVariOrderCost),
    unitHoldCost(unitHoldCost), unitPenaltyCost(unitPenaltyCost), truncatedQuantile(truncatedQuantile),
    max_I(max_I), min_I(min_I), pmf(std::move(pmf)) {
};


std::vector<double> NewsvendorDP::feasibleActions() const {
    const int QNum = static_cast<int>(capacity / stepSize);
    std::vector<double> actions(QNum);
    for (int i = 0; i < QNum; i = i + 1) {
        actions[i] = i * stepSize;
    }
    return actions;
}

State NewsvendorDP::stateTransitionFunction(const State &state, const double action, const double demand) const {
    double nextInventory = state.getInitialInventory() + action - demand;
    if (state.getPeriod() == 1) {
        (void) nextInventory;
    }
    if (nextInventory > 0) {
        (void) nextInventory;
    }
    nextInventory = nextInventory > max_I ? max_I : nextInventory;
    nextInventory = nextInventory < min_I ? min_I : nextInventory;

    const int nextPeriod = state.getPeriod() + 1;
    // C++11 引入了统一的列表初始化（Uniform Initialization），鼓励使用大括号 {} 初始化类
    const auto newState = State{nextPeriod, nextInventory};

    return newState;
}

double NewsvendorDP::immediateValueFunction(const State &state, const double action, const double demand) const {
    const double fixCost = action > 0 ? fixOrderCost : 0;
    const double variCost = action * unitVariOrderCost;
    double nextInventory = state.getInitialInventory() + action - demand;
    nextInventory = nextInventory > max_I ? max_I : nextInventory;
    nextInventory = nextInventory < min_I ? min_I : nextInventory;
    const double holdCost = std::max(unitHoldCost * nextInventory, 0.0);
    const double penaltyCost = std::max(-unitPenaltyCost * nextInventory, 0.0);

    const double totalCost = fixCost + variCost + holdCost + penaltyCost;
    return totalCost;
}

double NewsvendorDP::getOptAction(const State &state) {
    return cacheActions[state];
}

auto NewsvendorDP::getTable() const {
    size_t stateNums = cacheActions.size();
    std::vector<std::vector<double> > table(stateNums, std::vector<double>(3));
    int index = 0;
    for (const auto &[fst, snd]: cacheActions) {
        table[index][0] = fst.getPeriod();
        table[index][1] = fst.getInitialInventory();
        table[index][2] = snd;
        index++;
    }
    return table;
}

double NewsvendorDP::recursion(const State &state) {
    double bestQ = 0.0;
    double bestValue = std::numeric_limits<double>::max();
    const std::vector<double> actions = feasibleActions();
    for (const double action: feasibleActions()) {
        double thisValue = 0;
        for (auto demandAndProb: pmf[state.getPeriod() - 1]) {
            thisValue += demandAndProb[1] * immediateValueFunction(state, action, demandAndProb[0]);
            if (state.getPeriod() < T) {
                auto newState = stateTransitionFunction(state, action, demandAndProb[0]);
                (void) action;
                if (cacheValues.contains(newState)) {
                    // some issues here
                    thisValue += demandAndProb[1] * cacheValues[newState];
                } else {
                    thisValue += demandAndProb[1] * recursion(newState);
                }
            }
        }
        if (thisValue < bestValue) {
            bestValue = thisValue;
            bestQ = action;
        }
    }
    cacheActions[state] = bestQ;
    cacheValues[state] = bestValue;
    return bestValue;
}


int main() {
    std::vector<double> demands(30, 20);
    const std::string distribution_type = "poisson";
    constexpr int capacity = 100; // maximum ordering quantity
    constexpr double stepSize = 1.0;
    constexpr double fixOrderCost = 0;
    constexpr double unitVariOderCost = 1;
    constexpr double unitHoldCost = 2;
    constexpr double unitPenaltyCost = 10;
    constexpr double truncQuantile = 0.9999; // truncated quantile for the demand distribution
    constexpr double maxI = 500; // maximum possible inventory
    constexpr double minI = -300; // minimum possible inventory


    const auto pmf = ProbabilityMassFunctions(truncQuantile, stepSize, distribution_type).getPMF(demands);
    const size_t T = demands.size();
    auto model = NewsvendorDP(T, capacity, stepSize, fixOrderCost, unitVariOderCost, unitHoldCost, unitPenaltyCost,
                              truncQuantile, maxI, minI, pmf);

    const auto initialState = State(1, 0);
    const auto start_time = std::chrono::high_resolution_clock::now();
    const auto optValue = model.recursion(initialState);
    const auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "planning horizon is " << T << " periods" << std::endl;
    std::cout << "running time of C++ is " << duration << std::endl;
    std::cout << "Final optimal value is: " << optValue << std::endl;
     const auto optQ = model.getOptAction(initialState);
     std::cout << "Optimal Q is: " << optQ << std::endl;
    // auto table = model.getTable();
    return 0;
}
