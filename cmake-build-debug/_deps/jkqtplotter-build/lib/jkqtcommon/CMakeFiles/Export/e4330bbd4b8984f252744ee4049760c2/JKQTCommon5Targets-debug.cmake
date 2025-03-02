#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "JKQTPlotter5::JKQTCommon5" for configuration "Debug"
set_property(TARGET JKQTPlotter5::JKQTCommon5 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(JKQTPlotter5::JKQTCommon5 PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libJKQTCommon5_Debug.5.0.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libJKQTCommon5_Debug.5.0.0.dylib"
  )

list(APPEND _cmake_import_check_targets JKQTPlotter5::JKQTCommon5 )
list(APPEND _cmake_import_check_files_for_JKQTPlotter5::JKQTCommon5 "${_IMPORT_PREFIX}/lib/libJKQTCommon5_Debug.5.0.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
