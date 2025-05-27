#----------------------------------------------------------------
# Generated CMake target import file for configuration "None".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "norm::norm" for configuration "None"
set_property(TARGET norm::norm APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(norm::norm PROPERTIES
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libnorm.so.1"
  IMPORTED_SONAME_NONE "libnorm.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS norm::norm )
list(APPEND _IMPORT_CHECK_FILES_FOR_norm::norm "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libnorm.so.1" )

# Import target "norm::norm-static" for configuration "None"
set_property(TARGET norm::norm-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(norm::norm-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NONE "CXX"
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libnorm.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS norm::norm-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_norm::norm-static "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libnorm.a" )

# Import target "norm::protokit" for configuration "None"
set_property(TARGET norm::protokit APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(norm::protokit PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NONE "CXX"
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libprotokit.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS norm::protokit )
list(APPEND _IMPORT_CHECK_FILES_FOR_norm::protokit "${_IMPORT_PREFIX}/lib/aarch64-linux-gnu/libprotokit.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
