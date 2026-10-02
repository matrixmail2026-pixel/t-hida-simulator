cmake_minimum_required(VERSION 3.16)

project(t_hida_simulator LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build the C++ simulator
add_executable(t_hida_simulator main.cpp)

# Optional: build the C prototype as a separate executable
add_executable(hida_mining hida_bridge_hash.c)

# Optional compile flags
target_compile_options(t_hida_simulator PRIVATE
    -O2
    -Wall
    -Wextra
)

target_compile_options(hida_mining PRIVATE
    -O2
    -Wall
    -Wextra
)

# Output to bin directory
set_target_properties(t_hida_simulator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(hida_mining PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
