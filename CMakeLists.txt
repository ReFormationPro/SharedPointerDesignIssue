cmake_minimum_required(VERSION 3.5)

project(SharedPtrDesign LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
add_compile_options(-fPIE)

add_executable(SharedPtrDesign
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(SharedPtrDesign PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
