#----------------------------------------------------------------
# Generated CMake target import file for configuration "None".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cjson" for configuration "None"
set_property(TARGET cjson APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(cjson PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NONE "m"
  IMPORTED_LOCATION_NONE "/usr/lib/aarch64-linux-gnu/libcjson.so.1.7.15"
  IMPORTED_SONAME_NONE "libcjson.so.1"
  )

list(APPEND _cmake_import_check_targets cjson )
list(APPEND _cmake_import_check_files_for_cjson "/usr/lib/aarch64-linux-gnu/libcjson.so.1.7.15" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
