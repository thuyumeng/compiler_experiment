cmake_minimum_required(VERSION 3.0.0)
project(compilerC VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(compilerC main.cpp)

# build lex shared library 构建lex模块的二进制库
add_subdirectory(lex)
add_subdirectory(parser)

target_link_libraries(compilerC
    PRIVATE
        lex
        parser
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
