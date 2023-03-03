cmake_minimum_required(VERSION 3.10)
project(hello_world)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(useless)

#DOWNLOWD GIT SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}")
        endif()
    endif()

endif()

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC useless
    PUBLIC external/glfw/include)

target_link_directories(${PROJECT_NAME} 
    PRIVATE useless
    PRIVATE external/glfw/src)

target_link_libraries(${PROJECT_NAME} useless glfw)
