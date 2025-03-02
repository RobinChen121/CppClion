# Package-config file for JKQTCommon library
#   (part of JKQtPlotter, version )
#
# see: https://github.com/jkriege2/JKQtPlotter
# Copyright: (c) Jan Krieger <jan@jkrieger.de>
#


# package requires Qt 5/6
find_package(Qt5 COMPONENTS Core Gui Widgets Xml REQUIRED)

# include auto-generated targets.cmake file
include("${CMAKE_CURRENT_LIST_DIR}/JKQTCommon5Targets.cmake")

if(NOT TARGET JKQTPlotter::JKQTCommon)
  add_library(JKQTPlotter::JKQTCommon ALIAS JKQTPlotter5::JKQTCommon5)
endif()
