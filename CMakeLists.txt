cmake_minimum_required(VERSION 3.16)
project(CppProject CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E env ${CMAKE_BINARY_DIR}/CppBase
    USES_TERMINAL
)

add_subdirectory(src)
