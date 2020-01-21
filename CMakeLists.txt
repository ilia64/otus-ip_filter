cmake_minimum_required(VERSION 3.7)

set(MY_BUILD_PATH bin)
if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 1)
    set(MY_BUILD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

project(OTUS_CPP VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

message(">> Build: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

enable_testing()

add_subdirectory(version)
add_subdirectory(ip_filter)
