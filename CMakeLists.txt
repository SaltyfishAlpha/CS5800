cmake_minimum_required(VERSION 3.28)
project(CS5800)

set(CMAKE_CXX_STANDARD 17)

# Main executable (can be kept for general testing)
add_executable(CS5800 main.cpp)

# Auto-discover all problem directories
file(GLOB PROBLEM_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "problems/*")
foreach(PROBLEM_DIR ${PROBLEM_DIRS})
    # Check if it's a directory
    if(NOT IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${PROBLEM_DIR}")
        continue()
    endif()
    
    get_filename_component(PROBLEM_NAME ${PROBLEM_DIR} NAME)
    
    # Skip template directory
    if(${PROBLEM_NAME} STREQUAL "template")
        continue()
    endif()
    
    set(PROBLEM_MAIN "${PROBLEM_DIR}/main.cpp")
    
    # Only add if main.cpp exists
    if(EXISTS "${CMAKE_SOURCE_DIR}/${PROBLEM_MAIN}")
        add_executable(${PROBLEM_NAME} "${PROBLEM_MAIN}")
        
        # Define SOURCE_DIR macro so programs can find input files
        target_compile_definitions(${PROBLEM_NAME} PRIVATE SOURCE_DIR="${CMAKE_SOURCE_DIR}")
        
        # Set output directory
        set_target_properties(${PROBLEM_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/problems/${PROBLEM_NAME}"
        )
    endif()
endforeach()
