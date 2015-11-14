
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
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/external_cppformat )
if ( NOT STATICLIB_TOOLCHAIN MATCHES "linux_[^_]+_[^_]+" )
    staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/external_jansson )
endif ( )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/staticlib_utils )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/staticlib_io )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/staticlib_ranges )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/staticlib_reflection )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/staticlib_pimpl )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/deps/staticlib_serialization )
set ( ${PROJECT_NAME}_DEPS 
        staticlib_utils
        staticlib_io
        staticlib_ranges
        staticlib_reflection
        staticlib_pimpl
        staticlib_serialization
        crossguid
        jansson
        cppformat )
staticlib_pkg_check_modules ( ${PROJECT_NAME}_DEPS_PC REQUIRED ${PROJECT_NAME}_DEPS )

# build
file ( GLOB_RECURSE ${PROJECT_NAME}_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp )
source_group ( "src" FILES ${${PROJECT_NAME}_SRC} )
file ( GLOB_RECURSE ${PROJECT_NAME}_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/*.hpp )
source_group ( "include" FILES ${${PROJECT_NAME}_HEADERS} )
set ( ${PROJECT_NAME}_INCLUDES 
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/deps/tclap/include
        ${CMAKE_CURRENT_LIST_DIR}/deps/asio/asio/include
        ${${PROJECT_NAME}_DEPS_PC_INCLUDE_DIRS} )
set ( ${PROJECT_NAME}_DEFINITIONS 
        -DASIO_STANDALONE
        -DASIO_HAS_STD_CHRONO )
if ( ${CMAKE_CXX_COMPILER_ID}x MATCHES "MSVCx" )    
    set ( ${PROJECT_NAME}_DEFINITIONS ${${PROJECT_NAME}_DEFINITIONS}
            -D_CRT_SECURE_NO_WARNINGS
            -D_SCL_SECURE_NO_WARNINGS
            -D_WIN32_WINNT=0x0501 
            -DWIN32_LEAN_AND_MEAN )
endif ( )            

# executable
add_executable ( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS} )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE ${${PROJECT_NAME}_INCLUDES} )
target_link_libraries ( ${PROJECT_NAME} ${${PROJECT_NAME}_DEPS_PC_LIBRARIES} )
if ( STATICLIB_TOOLCHAIN MATCHES "linux_[^_]+_[^_]+" )
    target_link_libraries ( ${PROJECT_NAME} pthread )
endif ( )
target_compile_options ( ${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DEPS_PC_CFLAGS_OTHER} )
target_compile_definitions ( ${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DEFINITIONS} )

# library for tests
option ( ${PROJECT_NAME}_ENABLE_TESTS "Generate doxyfile and exit build" OFF )
if ( ${PROJECT_NAME}_ENABLE_TESTS )
# http://stackoverflow.com/q/1941443/314015
if ( STATICLIB_TOOLCHAIN MATCHES "windows_[^_]+_[^_]+" )
    set ( ${PROJECT_NAME}_TEST_LIBRARY_TYPE STATIC )
else ( )
    set ( ${PROJECT_NAME}_TEST_LIBRARY_TYPE SHARED )
endif ( )    
    add_library ( ${PROJECT_NAME}_testing ${${PROJECT_NAME}_TEST_LIBRARY_TYPE} ${${PROJECT_NAME}_SRC} )
    target_include_directories ( ${PROJECT_NAME}_testing BEFORE PRIVATE ${${PROJECT_NAME}_INCLUDES} )
    target_link_libraries ( ${PROJECT_NAME}_testing ${${PROJECT_NAME}_DEPS_PC_LIBRARIES} )
    if ( STATICLIB_TOOLCHAIN MATCHES "linux_[^_]+_[^_]+" )
        target_link_libraries ( ${PROJECT_NAME}_testing pthread )
    endif ( )
    target_compile_options ( ${PROJECT_NAME}_testing PRIVATE ${${PROJECT_NAME}_DEPS_PC_CFLAGS_OTHER} )
    target_compile_definitions ( ${PROJECT_NAME}_testing PRIVATE ${${PROJECT_NAME}_DEFINITIONS} )
endif ( )
