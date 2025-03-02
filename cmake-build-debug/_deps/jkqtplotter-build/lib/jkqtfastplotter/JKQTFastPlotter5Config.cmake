# Package-config file for JKQTFastPlotter library
#   (part of JKQtPlotter, version 5.0.0)
#
# see: https://github.com/jkriege2/JKQtPlotter
# Copyright: (c) Jan Krieger <jan@jkrieger.de>
#


# package requires Qt 5/6
find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL REQUIRED)
if(${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL "6")
    find_package(Qt5 REQUIRED COMPONENTS OpenGLWidgets)
endif()
find_package(JKQTCommon5 REQUIRED PATHS ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_MODULE_PATH})

# include auto-generated targets.cmake file
include("${CMAKE_CURRENT_LIST_DIR}/JKQTFastPlotter5Targets.cmake")

if(NOT TARGET JKQTPlotter::JKQTFastPlotter)
  add_library(JKQTPlotter::JKQTFastPlotter ALIAS JKQTPlotter5::JKQTFastPlotter5)
endif()
