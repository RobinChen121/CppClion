/*
 * Created by Zhen Chen on 2025/3/6.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */
#include <iostream>
#include <pybind11/embed.h> // everything needed for embedding
namespace py = pybind11;

int main() {
    py::scoped_interpreter guard{}; // start the interpreter and keep it alive
    try {
        py::module_ math = py::module_::import("math");
        double result = math.attr("sqrt")(16).cast<double>();
        std::cout << "sqrt(16) = " << result << std::endl;
    } catch (py::error_already_set &e) {
        std::cerr << "Python error: " << e.what() << std::endl;
    }

    return 0;
}
