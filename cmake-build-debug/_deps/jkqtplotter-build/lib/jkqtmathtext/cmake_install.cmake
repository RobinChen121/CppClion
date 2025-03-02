# Install script for directory: /Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext

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
  include("/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmathtext/nodes/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmathtext/parsers/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE RENAME "JKQTMathText5_XITS_LICENSE.txt" FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/resources/xits/OFL.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE RENAME "JKQTMathText5_XITS_README.md" FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/resources/xits/README.md")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE RENAME "JKQTMathText5_FIRAMATH_LICENSE" FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/resources/firaMath/LICENSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE RENAME "JKQTMathText5_FIRAMATH_README.md" FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/resources/firaMath/README.md")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output/libJKQTMathText5_Debug.5.0.0.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTMathText5_Debug.5.0.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTMathText5_Debug.5.0.0.dylib")
    execute_process(COMMAND /opt/anaconda3/bin/install_name_tool
      -delete_rpath "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output"
      -delete_rpath "/opt/anaconda3/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTMathText5_Debug.5.0.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTMathText5_Debug.5.0.0.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output/libJKQTMathText5_Debug.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jkqtmathtext" TYPE FILE FILES
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/jkqtmathtext.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/jkqtmathtexttools.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/jkqtmathtextlabel.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/jkqtmathtext_imexport.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jkqtmathtext/nodes" TYPE FILE FILES
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtexttextnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextboxinstructionnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextmodifyenvironmentnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextbracenode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextdecoratednode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextfracnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextinstructionnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextlistnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextverticallistnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtexthorizontallistnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextmatrixnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextsqrtnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextsubsupernode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextsymbolnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextnodetools.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextwhitespacenode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextnoopnode.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/nodes/jkqtmathtextverbatimnode.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jkqtmathtext/parsers" TYPE FILE FILES
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/parsers/jkqtmathtextparser.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmathtext/parsers/jkqtmathtextlatexparser.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTMathText5Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTMathText5Targets.cmake"
         "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmathtext/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTMathText5Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTMathText5Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTMathText5Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmathtext/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTMathText5Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmathtext/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTMathText5Targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmathtext/JKQTMathText5Version.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmathtext/JKQTMathText5Config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmathtext/JKQTMathText5_Readme.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/LICENSE")
endif()

