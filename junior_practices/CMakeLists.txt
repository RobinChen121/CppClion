set(RUN_NAME junior_practice) # 设置运行程序的名字

# 创建可执行程序，需要运行的 cpp 文件放在这里
add_executable(${RUN_NAME}
        fibonacci_test3.cpp
)

# 查找 Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
# 链接 Boost, Qt
target_link_libraries(${RUN_NAME} ${Boost_LIBRARIES} Qt6::Widgets)

#-----------------------------------
# OpenMP
target_link_libraries(${RUN_NAME} ${OpenMP_LIBRARY})