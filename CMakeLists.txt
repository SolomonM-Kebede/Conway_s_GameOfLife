cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to enable OpenMP
option(ENABLE_OPENMP "Enable OpenMP support" ON)

# Source files
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Copy data files (adjust extension if needed)
file(GLOB DATA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.txt")
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_BINARY_DIR})

# Create executable
add_executable(game ${SOURCES})
target_include_directories(game PUBLIC include)

# Link OpenMP if enabled
if (ENABLE_OPENMP)
    find_package(OpenMP REQUIRED)
    target_link_libraries(game PUBLIC OpenMP::OpenMP_CXX)
endif()