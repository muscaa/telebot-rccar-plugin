cmake_minimum_required(VERSION 3.23)
project(telebot-template-plugin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# SDK includes
file(GLOB SDK_INCLUDES "sdks/*/include.cmake")

foreach(SDK_INCLUDE ${SDK_INCLUDES})
    message(STATUS "Including SDK: ${SDK_INCLUDE}")

    get_filename_component(SDK_DIR "${SDK_INCLUDE}" DIRECTORY)
    get_filename_component(SDK_NAME "${SDK_DIR}" NAME)

    include(${SDK_INCLUDE})
endforeach()

# Plugin
add_subdirectory(plugin)
