
cmake_minimum_required ( VERSION 2.8.12 )

# toolchain setup
set ( STATICLIB_TOOLCHAIN linux_amd64_gcc CACHE STRING "toolchain triplet" )
if ( NOT DEFINED STATICLIB_CMAKE )
    set ( STATICLIB_CMAKE ${CMAKE_CURRENT_LIST_DIR}/cmake CACHE INTERNAL "" )
    set ( CMAKE_TOOLCHAIN_FILE ${STATICLIB_CMAKE}/toolchains/${STATICLIB_TOOLCHAIN}.cmake CACHE INTERNAL "" )
endif ( )

# project
project ( shell_helper CXX )
include ( ${STATICLIB_CMAKE}/staticlibs_common.cmake )

# dependencies
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/external_crossguid )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/staticlib_utils )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/staticlib_pimpl )
set ( ${PROJECT_NAME}_DEPS 
        staticlib_utils
        staticlib_pimpl
        crossguid )
staticlib_pkg_check_modules ( ${PROJECT_NAME}_DEPS_PC REQUIRED ${PROJECT_NAME}_DEPS )

# build
file ( GLOB_RECURSE ${PROJECT_NAME}_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp )
source_group ( "src" FILES ${${PROJECT_NAME}_SRC} )
file ( GLOB_RECURSE ${PROJECT_NAME}_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/*.hpp )
source_group ( "include" FILES ${${PROJECT_NAME}_HEADERS} )
set ( ${PROJECT_NAME}_INCLUDES 
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/deps/tclap/include
        ${${PROJECT_NAME}_DEPS_PC_INCLUDE_DIRS} )

# executable
add_executable ( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS} )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE ${${PROJECT_NAME}_INCLUDES} )
target_link_libraries ( ${PROJECT_NAME} ${${PROJECT_NAME}_DEPS_PC_LIBRARIES} )
target_compile_options ( ${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DEPS_PC_CFLAGS_OTHER} )

# library for tests
option ( ${PROJECT_NAME}_ENABLE_TESTS "Generate doxyfile and exit build" OFF )
if ( ${PROJECT_NAME}_ENABLE_TESTS )
    add_library ( ${PROJECT_NAME}_test SHARED ${${PROJECT_NAME}_SRC} )
    target_include_directories ( ${PROJECT_NAME}_test BEFORE PRIVATE ${${PROJECT_NAME}_INCLUDES} )
    target_link_libraries ( ${PROJECT_NAME}_test ${${PROJECT_NAME}_DEPS_PC_LIBRARIES} )
    target_compile_options ( ${PROJECT_NAME}_test PRIVATE ${${PROJECT_NAME}_DEPS_PC_CFLAGS_OTHER} )
endif ( )
