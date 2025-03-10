set(RUN_NAME inventory) # 设置运行程序的名字

set(CMAKE_BUILD_TYPE Release) # 运行 Debug 还是 Release

#set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-omit-frame-pointer -pthread")
# 创建可执行程序，需要运行的 cpp 文件放在这里
add_executable(${RUN_NAME}
        NewsvendorParallel.cpp
        #        newsvendor.cpp
        PMF.cpp
        State.cpp
)

#-----------------------------------
# OpenMP, Boost
find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(${RUN_NAME} ${OpenMP_LIBRARY} ${Boost_LIBRARIES})