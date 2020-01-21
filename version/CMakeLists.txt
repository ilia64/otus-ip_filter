cmake_minimum_required(VERSION 3.7)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)

add_executable(version main.cpp)

add_library(version_lib lib.cpp)

add_executable(test_version test_version.cpp)

set_target_properties(version version_lib test_version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

set_target_properties(test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
        )

target_link_libraries(version
        version_lib
        Threads::Threads
        )

target_link_libraries(test_version
        ${Boost_LIBRARIES}
        version_lib
        )

add_test(version_tests test_version)

install(TARGETS version RUNTIME DESTINATION ${MY_BUILD_PATH})
