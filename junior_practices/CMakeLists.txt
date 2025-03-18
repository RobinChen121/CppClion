set(RUN_NAME junior_practice) # 设置运行程序的名字

# 创建可执行程序，需要运行的 cpp 文件放在这里
add_executable(${RUN_NAME}
        #        MyClass.cpp
        sets_test.cpp
)

# 查找 Qt5
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
if (QT5_FOUND)
    message(STATUS "qtfound")
else ()
    message("not found")
endif ()
## 链接 Boost, Qt
#target_link_libraries(${RUN_NAME} ${Boost_LIBRARIES} Qt5::Widgets)

# 需要手动设置 OpenMP 头文件和库路径
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

#-----------------------------------
# OpenMP, Eigen3
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
target_link_libraries(${RUN_NAME} ${OpenMP_LIBRARY} ${Boost_LIBRARIES} Qt5::Widgets Eigen3::Eigen)

# spdlog
find_package(spdlog)
target_link_libraries(${RUN_NAME} spdlog::spdlog)