set(RUN_NAME junior_practice) # 设置运行程序的名字

# 创建可执行程序，需要运行的 cpp 文件放在这里
add_executable(${RUN_NAME}
        MyClass.cpp
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

#-----------------------------------
# OpenMP, Eigen3
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
target_link_libraries(${RUN_NAME} ${OpenMP_LIBRARY} ${Boost_LIBRARIES} Qt5::Widgets)