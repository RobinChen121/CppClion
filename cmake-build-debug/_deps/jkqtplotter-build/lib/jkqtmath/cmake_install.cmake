# Install script for directory: /Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output/libJKQTMath5_Debug.5.0.0.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTMath5_Debug.5.0.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTMath5_Debug.5.0.0.dylib")
    execute_process(COMMAND /opt/anaconda3/bin/install_name_tool
      -delete_rpath "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output"
      -delete_rpath "/opt/anaconda3/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTMath5_Debug.5.0.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libJKQTMath5_Debug.5.0.0.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/output/libJKQTMath5_Debug.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/jkqtmath" TYPE FILE FILES
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtmath_imexport.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpalgorithms.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtplinalgtools.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpmathparser.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtparraytools.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpstatisticstools.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpstatbasics.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpstathistogram.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpstatkde.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpstatregression.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpstatpoly.h"
    "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/lib/jkqtmath/jkqtpstatgrouped.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTMath5Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTMath5Targets.cmake"
         "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmath/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTMath5Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTMath5Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5/JKQTMath5Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmath/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTMath5Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmath/CMakeFiles/Export/e4330bbd4b8984f252744ee4049760c2/JKQTMath5Targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmath/JKQTMath5Version.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JKQTPlotter5" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmath/JKQTMath5Config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-build/lib/jkqtmath/JKQTMath5_Readme.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/JKQTPlotter" TYPE FILE FILES "/Users/zhenchen/CLionProjects/CppClion/cmake-build-debug/_deps/jkqtplotter-src/LICENSE")
endif()

