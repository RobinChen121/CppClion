
cmake_minimum_required(VERSION 3.30)
project(CppClion)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BUILD_TYPE Debug) # 运行 debug
#-----------------------------------
# 设置构建类型为 Release, 开启 o2,o3做准备
set(CMAKE_BUILD_TYPE Release) # 开了这个就不能 debug 了

# 修改 Release 模式下的编译选项，强制使用 -O3（你也可以改为 -O2）
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

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

#-----------------------------------
add_executable(${PROJECT_NAME}
        #        main.cpp
        #        stochastic_inventory/NewsvendorC.c
        stochastic_inventory/NewsvendorParallelGrok.cpp
        #        stochastic_inventory/NewsvendorGrok.cpp
        #        stochastic_inventory/Newsvendor.cpp
        #        stochastic_inventory/ProbabilityMassFunctions.cpp
        #        stochastic_inventory/State.cpp

)  # no need to put .h file here

# 查找 Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

# 链接 Boost, Qt, JKQtPlotter
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Qt6::Widgets)


#-----------------------------------
# jQTPlotter
