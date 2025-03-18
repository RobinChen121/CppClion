
cmake_minimum_required(VERSION 3.30)
project(CppClion)

# 使用 Conan 生成的 CMake 配置
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/build/conan_toolchain.cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子文件夹
add_subdirectory(linear_programming) # 告诉 CMake 在小括号那目录下查找 CMakeLists.txtß
add_subdirectory(junior_practices)
add_subdirectory(stochastic_inventory)
add_subdirectory(utils)

set(CMAKE_BUILD_TYPE Debug) # 运行 Debug 还是 Release
# 强制使用 -O3（你也可以改为 -O2）
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif ()

#-----------------------------------
add_executable(${PROJECT_NAME}
        main.cpp
        #        stochastic_inventory/NewsvendorC.c

)  # no need to put .h file here

find_package(Eigen3 REQUIRED)
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)

#------------------------
# 如果 Boost 安装在非标准路径，手动设置 BOOST_ROOT 和相关变量
#set(BOOST_ROOT "/opt/homebrew/Cellar/boost/1.87.0")  # 根据实际路径修改，比如 /usr/local 对于 Intel 机器
#set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
#set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
## 查找 Boost（如果只需要头文件库，可以不指定 COMPONENTS）
#find_package(Boost REQUIRED COMPONENTS filesystem system)
#if (Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
#else ()
#    message(FATAL_ERROR "Could not find Boost!")
#endif ()
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


#-----------------------------------
## 查找 Pybind11, 执行 python 代码，很鸡肋，只能弄一些简单的，比较复杂
## 查找 JKQTPlotter, 无法运行


