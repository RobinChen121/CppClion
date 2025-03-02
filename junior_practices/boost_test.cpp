//
// Created by Zhen Chen on 2025/2/22.
//

#include <boost/math/distributions/normal.hpp> // for normal_distribution
using boost::math::normal; // typedef provides default type is double.

#include <iostream>
using std::cout; using std::endl;

int main()
{
cout << "Example: Normal distribution, Miscellaneous Applications.\n";

    // Construct a standard normal distribution s
    normal s; // (default mean = zero, and standard deviation = unity)
    cout << "Standard normal distribution, mean = " << s.mean()
        << ", standard deviation = " << s.standard_deviation() << endl;

    cout << "cdf is " << cdf(s, 0) << endl;
    return 0;
}