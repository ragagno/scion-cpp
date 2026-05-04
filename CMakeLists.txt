cmake_minimum_required(VERSION 3.28)

project(scion VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(SCION_HEADERS_CONFIGURED
    include/scion/constants.hpp
)

set(SCION_HEADERS
    include/scion/scion.hpp

    include/scion/core/core.hpp
    include/scion/core/types.hpp
    include/scion/core/traits.hpp
    include/scion/core/arithmetic.hpp

    include/scion/util/util.hpp
    include/scion/util/assert.hpp
    include/scion/util/log.hpp

    include/scion/prelude/prelude.hpp
    include/scion/prelude/types.hpp
)

set(SCION_SOURCES
    sources/scion/scion.cpp
)

list(TRANSFORM SCION_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM SCION_HEADERS PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

foreach(HEADER_HPP IN LISTS SCION_HEADERS_CONFIGURED)
    string(REGEX REPLACE "\\.hpp$" ".ipp" HEADER_IPP "${HEADER_HPP}")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_IPP}" "${CMAKE_CURRENT_BINARY_DIR}/${HEADER_HPP}" @ONLY)
    list(APPEND SCION_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/${HEADER_HPP}")
endforeach()

add_library(scion STATIC)
add_library(scion::scion ALIAS scion)
target_sources(scion PRIVATE ${SCION_SOURCES} PUBLIC FILE_SET HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include" FILES ${SCION_HEADERS})
target_include_directories(scion PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include> $<INSTALL_INTERFACE:include>)
target_compile_features(scion PUBLIC cxx_std_23)
set_target_properties(scion PROPERTIES CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
target_compile_options(scion PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra> $<$<CXX_COMPILER_ID:MSVC>:/W4>)
target_compile_definitions(scion PRIVATE $<$<PLATFORM_ID:Windows>:SCION_PLATFORM_WINDOWS> $<$<PLATFORM_ID:Darwin>:SCION_PLATFORM_MAC> $<$<PLATFORM_ID:Linux>:SCION_PLATFORM_LINUX> $<$<CXX_COMPILER_ID:MSVC>:SCION_COMPILER_MSVC> $<$<CXX_COMPILER_ID:Clang>:SCION_COMPILER_CLANG> $<$<CXX_COMPILER_ID:AppleClang>:SCION_COMPILER_CLANG> $<$<CXX_COMPILER_ID:GNU>:SCION_COMPILER_GCC> $<$<CONFIG:Debug>:SCION_CONFIGURATION_DEBUG> $<$<CONFIG:Release>:SCION_CONFIGURATION_RELEASE> $<$<CONFIG:RelWithDebInfo>:SCION_CONFIGURATION_PROFILE>)

install(TARGETS scion EXPORT scion-targets FILE_SET HEADERS)

install(EXPORT scion-targets NAMESPACE scion:: DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/scion")

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/scion-config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/scion-config.cmake" INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/scion")
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/scion-config-version.cmake" VERSION ${PROJECT_VERSION} COMPATIBILITY AnyNewerVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/scion-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/scion-config-version.cmake" DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/scion")

if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory(tests)
endif()
