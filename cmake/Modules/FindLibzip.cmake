find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(PC_LIBZIP QUIET libzip)
endif()

find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(PC_LIBZIP QUIET libzip)
endif()

find_path(LIBZIP_INCLUDE_DIR
  NAMES zip.h
  HINTS ${PC_LIBZIP_INCLUDE_DIRS})

find_path(LIBZIP_CONF_INCLUDE_DIR
  NAMES zipconf.h
  HINTS ${PC_LIBZIP_INCLUDE_DIRS})

find_library(LIBZIP_LIBRARY
  NAMES zip libzip
  HINTS ${PC_LIBZIP_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libzip
  REQUIRED_VARS LIBZIP_LIBRARY LIBZIP_INCLUDE_DIR LIBZIP_CONF_INCLUDE_DIR
  VERSION_VAR   LIBZIP_VERSION)

if(libzip_FOUND AND NOT TARGET libzip::zip)
  add_library(libzip::zip UNKNOWN IMPORTED)
  set_target_properties(libzip::zip PROPERTIES
    IMPORTED_LOCATION "${LIBZIP_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBZIP_INCLUDE_DIR};${LIBZIP_CONF_INCLUDE_DIR}")
endif()

mark_as_advanced(LIBZIP_INCLUDE_DIR LIBZIP_CONF_INCLUDE_DIR LIBZIP_LIBRARY)
