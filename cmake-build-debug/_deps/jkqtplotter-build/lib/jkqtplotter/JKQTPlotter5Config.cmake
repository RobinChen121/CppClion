# Package-config file for JKQTPlotter library
#   (part of JKQtPlotter, version 5.0.0)
#
# see: https://github.com/jkriege2/JKQtPlotter
# Copyright: (c) Jan Krieger <jan@jkrieger.de>
#

# package requires Qt 5
find_package(Qt5 COMPONENTS Core Gui Widgets Svg Xml OpenGL PrintSupport REQUIRED)
find_package(JKQTCommon5 REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_MODULE_PATH})
find_package(JKQTMath5 REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_MODULE_PATH})
find_package(JKQTMathText5 REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_MODULE_PATH})

# include auto-generated targets.cmake file
include("${CMAKE_CURRENT_LIST_DIR}/JKQTPlotter5Targets.cmake")


if(NOT TARGET JKQTPlotter::JKQTPlotter)
  add_library(JKQTPlotter::JKQTPlotter ALIAS JKQTPlotter5::JKQTPlotter5)
endif()
