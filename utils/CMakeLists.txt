set(RUN_NAME utils) # 设置运行程序的名字

# 创建可执行程序，需要运行的 cpp 文件放在这里
add_executable(${RUN_NAME}
        #        gurobi_test.cpp
        removeDuplicates.cpp
        #        my_solver/Var.cpp
        #        my_solver/Model.cpp
)

#-----------------------------------
# Boost
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
target_link_libraries(${RUN_NAME} ${Boost_LIBRARIES})


