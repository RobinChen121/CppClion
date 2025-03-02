# Package-config file for JKQTMath library
#   (part of JKQtPlotter, version 5.0.0)
#
# see: https://github.com/jkriege2/JKQtPlotter
# Copyright: (c) Jan Krieger <jan@jkrieger.de>
#


# package requires Qt 5/6
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(JKQTCommon5 REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_MODULE_PATH})

# include auto-generated targets.cmake file
include("${CMAKE_CURRENT_LIST_DIR}/JKQTMath5Targets.cmake")


if(NOT TARGET JKQTPlotter::JKQTMath)
  add_library(JKQTPlotter::JKQTMath ALIAS JKQTPlotter5::JKQTMath5)
endif()
