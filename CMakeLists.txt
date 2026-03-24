cmake_minimum_required(VERSION 3.21)

# Set the version
project(SimpleFem VERSION "0.9.0" LANGUAGES CXX)
include(GNUInstallDirs)

if (WIN32)
    # Windows requires all symbols to be manually exported.
    # This flag exports all symbols automatically, as in Unix.
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Source files
add_library(simplefem)

# Set the C++ standard
target_compile_features(simplefem PUBLIC cxx_std_20)

target_include_directories(simplefem PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set(HEADERS_simplefem
  ${CMAKE_CURRENT_SOURCE_DIR}/simplefem/lagrange.h
  ${CMAKE_CURRENT_SOURCE_DIR}/simplefem/polynomials.h
)
target_sources(simplefem PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/simplefem/lagrange.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/simplefem/polynomials.cpp
)
# Configure the library
set_target_properties(simplefem PROPERTIES PUBLIC_HEADER simplefem/lagrange.h)
set_target_properties(simplefem PROPERTIES PRIVATE_HEADER "${HEADERS_simplefem}")
target_include_directories(simplefem PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_SOURCE_DIR}>")

if (UNIX)
    list(APPEND SIMPLEFEM_DEVELOPER_FLAGS -O2;-g;-pipe)
    list(APPEND SIMPLEFEM_COMPILER_FLAGS -Wall;-Werror;-Wextra;-Wno-comment;-pedantic;)
    target_compile_options(simplefem PRIVATE "$<$<OR:$<CONFIG:Debug>,$<CONFIG:Developer>>:${SIMPLEFEM_COMPILER_FLAGS}>")
    target_compile_options(simplefem PRIVATE $<$<CONFIG:Developer>:${SIMPLEFEM_DEVELOPER_FLAGS}>)
endif()

install(TARGETS simplefem
  EXPORT SimpleFemTargets
  RUNTIME_DEPENDENCY_SET dependencies
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/simplefem
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT RuntimeExecutables
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
)
if (INSTALL_RUNTIME_DEPENDENCIES AND WIN32)
  # https://discourse.cmake.org/t/migration-experiences-comparison-runtime-dependency-set-vs-fixup-bundle-bundleutilities
  install(RUNTIME_DEPENDENCY_SET dependencies DESTINATION ${CMAKE_INSTALL_BINDIR} PRE_EXCLUDE_REGEXES [[api-ms-win-.*]] [[ext-ms-.*]] POST_EXCLUDE_REGEXES [[.*(\\|/)system32(\\|/).*\.dll]])
endif()

# Configure CMake helpers
include(CMakePackageConfigHelpers)
write_basic_package_version_file(SimpleFemConfigVersion.cmake VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion)
configure_package_config_file(SimpleFemConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/SimpleFemConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/simplefem)

# Install CMake files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SimpleFemConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/SimpleFemConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/simplefem COMPONENT Development)
install(EXPORT SimpleFemTargets FILE SimpleFemTargets.cmake NAMESPACE SimpleFem::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/simplefem)
