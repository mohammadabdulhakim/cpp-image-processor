cmake_minimum_required(VERSION 3.15)

project(ImageProcessing CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the main executable
add_executable(${PROJECT_NAME} main.cpp)

# Post-build step: copy assets/ to the same folder as the executable (Debug or Release)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
