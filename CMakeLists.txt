
cmake_minimum_required(VERSION 3.30)
project(CppClion)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BUILD_TYPE Debug) # 运行 debug 还是 release

# 修改 Release 模式下的编译选项，强制使用 -O3（你也可以改为 -O2）
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()

#------------------------
# 如果 Boost 安装在非标准路径，手动设置 BOOST_ROOT 和相关变量
set(BOOST_ROOT "/opt/homebrew/Cellar/boost/1.87.0")  # 根据实际路径修改，比如 /usr/local 对于 Intel 机器
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
# 查找 Boost（如果只需要头文件库，可以不指定 COMPONENTS）
find_package(Boost REQUIRED COMPONENTS filesystem system)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else ()
    message(FATAL_ERROR "Could not find Boost!")
endif ()
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

#-----------------------------------
add_executable(${PROJECT_NAME}
        #        main.cpp
        #        stochastic_inventory/NewsvendorC.c
        #        stochastic_inventory/NewsvendorParallelGrok.cpp
        #        stochastic_inventory/NewsvendorGrok.cpp
        #        stochastic_inventory/Newsvendor.cpp
        #        stochastic_inventory/ProbabilityMassFunctions.cpp
        #        stochastic_inventory/State.cpp
        junior_practices/fibonacci_test3.cpp
        #        junior_practices/draw_gnuplot.cpp
        #        linear_programming/gurobi_test.cpp

)  # no need to put .h file here

#-----------------------------------
# OpenMP
# 设置 OpenMP 头文件和库路径
set(OpenMP_INCLUDE_DIR "/opt/homebrew/Cellar/libomp/20.1.0/include")
set(OpenMP_LIBRARY "/opt/homebrew/Cellar/libomp/20.1.0/lib/libomp.dylib")
# 手动设置 OpenMP 相关的编译和链接选项
set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I${OpenMP_INCLUDE_DIR}")
set(OpenMP_CXX_LIBS "-L${OpenMP_LIB_DIR} -lomp")
# 应用 OpenMP 选项
# 这两行命令使得运行当前并行计算 cpp 等同于在命令行中的设置
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}") # CMAKE_CXX_FLAGS 变量用于存储 C++ 编译器的全局编译选项（flags）
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_CXX_LIBS}") # CMAKE_EXE_LINKER_FLAGS 变量用于存储 链接时的额外选项
# 添加 OpenMP 头文件路径和库路径
include_directories(${OpenMP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES} ${OpenMP_LIBRARY})

# 添加子文件夹
add_subdirectory(linear_programming) # 告诉 CMake 在小括号那目录下查找 CMakeLists.txtß
add_subdirectory(junior_practices)


### 查找 Pybind11, 执行 python 代码，很鸡肋，只能弄一些简单的，比较复杂
#find_package(pybind11 PATHS /opt/anaconda3/lib/python3.12/site-packages/pybind11/share/cmake)
#target_link_libraries(${PROJECT_NAME} pybind11::embed)
#
## 查找 Jkqtplotter, 无法运行
#find_package(JKQtPlotter PATHS /Users/zhenchen/Documents/JKQtPlotter-master/cmake)
#include_directories("/Users/zhenchen/Documents/JKQtPlotter-master/lib")
#target_link_libraries(${PROJECT_NAME} JKQtPlotter)

