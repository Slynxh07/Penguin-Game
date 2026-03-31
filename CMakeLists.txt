cmake_minimum_required(VERSION 3.10)
project(Penguin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib 5.5 QUIET)

if (NOT raylib_FOUND)
    message(STATUS "raylib not found, fetching from github")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
    )
    FetchCOntent_MakeAvailable(raylib)
endif()

file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")
add_executable(${PROJECT_NAME} ${SRC_FILES})

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)


target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} raylib)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME}
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
endif()