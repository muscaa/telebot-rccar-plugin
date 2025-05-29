set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>/plugin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>/plugin")

# Sources
file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} SHARED
    ${MAIN_SOURCES}
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
)
target_include_directories(${PROJECT_NAME} PRIVATE
    include
)

# VCPKG links
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${TELEBOT_API}
)
