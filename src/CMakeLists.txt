set(SOURCES
    Parser.cpp
    main.cpp
)

include_directories(.)
add_executable(CppBase ${SOURCES})
install(TARGETS CppBase RUNTIME DESTINATION ${CMAKE_BINARY_DIR})
