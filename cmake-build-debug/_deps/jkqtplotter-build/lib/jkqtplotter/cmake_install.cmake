# Install script for directory: /Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtplotter/graphs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtplotter/gui/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output/libJKQTPlotter5_Debug.5.0.0.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTPlotter5_Debug.5.0.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTPlotter5_Debug.5.0.0.dylib")
    execute_process(COMMAND /opt/anaconda3/bin/install_name_tool
      -delete_rpath "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output"
      -delete_rpath "/opt/anaconda3/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTPlotter5_Debug.5.0.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTPlotter5_Debug.5.0.0.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output/libJKQTPlotter5_Debug.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jkqtplotter" TYPE FILE FILES
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtptools.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpbaseelements.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpbaseplotter.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpdatastorage.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpgraphsbase.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpgraphsbaseerrors.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpgraphsbasestylingmixins.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtplotter.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtplotterstyle.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpkeystyle.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpkey.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpbaseplotterstyle.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpcoordinateaxes.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpcoordinateaxesstyle.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpimagetools.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtpgraphsbasestyle.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtplotter_configmacros.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/jkqtplotter_imexport.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jkqtplotter/graphs" TYPE FILE FILES
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpboxplot.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpboxplotbase.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpboxplotstylingmixins.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpevaluatedfunctionbase.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpevaluatedfunction.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpfilledcurve.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpfinancial.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpgeometric.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpgeoannotations.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpgeobase.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpgeolines.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpgeoshapes.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpimage.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpimpulses.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpparsedfunction.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtppeakstream.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpsinglecolumnsymbols.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpimageoverlays.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpcontour.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpimagergb.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpviolinplot.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpviolinplotstylingmixins.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpstatisticsadaptors.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpscatter.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtprange.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpspecialline.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpbarchartbase.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpbarchart.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpevaluatedparametriccurve.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtplines.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpgraphlabelstylemixin.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpgraphlabels.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/graphs/jkqtpvectorfield.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jkqtplotter/gui" TYPE FILE FILES
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/gui/jkqtpcomboboxes.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/gui/jkqtpenhancedspinboxes.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/gui/jkqtpenhancedtableview.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/gui/jkqtpgraphsmodel.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtplotter/gui/jkvanishqtoolbar.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTPlotter5Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTPlotter5Targets.cmake"
         "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtplotter/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTPlotter5Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTPlotter5Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTPlotter5Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtplotter/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTPlotter5Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtplotter/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTPlotter5Targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtplotter/JKQTPlotter5Version.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtplotter/JKQTPlotter5Config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtplotter/JKQTPlotter5_Readme.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/LICENSE")
endif()

