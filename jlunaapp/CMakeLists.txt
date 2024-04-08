cmake_minimum_required(VERSION 3.27)
project(jlunaapp)

set(CMAKE_CXX_STANDARD 20)

add_executable(jlunaapp main.cpp)

find_library(jluna REQUIRED
        NAMES jluna
        PATHS "D:/jjluna/lib"
)

target_link_libraries(jlunaapp PRIVATE
        "${jluna}"
        "C:/soft_using/julia-1.10.2/lib/libjulia.dll.a"
)
target_include_directories(jlunaapp PRIVATE
        "D:/jjluna/include/jluna"
        "C:/soft_using/julia-1.10.2/include/julia"
)
target_compile_features(jlunaapp PRIVATE cxx_std_20)